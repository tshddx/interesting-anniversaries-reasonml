type routeStatus =
  | Active
  | Inactive;

type state = {routeStatus};

type action =
  | ChangeRouteStatus(routeStatus);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRouteStatus(routeStatus) =>
    ReasonReact.Update({routeStatus: routeStatus})
  };

let component = ReasonReact.reducerComponent("Link");

let handleClick = (path, event) =>
  /* the default action will reload the page, which will cause us to lose state */
  if (! ReactEventRe.Mouse.defaultPrevented(event)) {
    ReactEventRe.Mouse.preventDefault(event);
    ReasonReact.Router.push(path);
  };

let make = (~path, children) => {
  ...component,
  reducer,
  initialState: () => {routeStatus: Inactive},
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url => {
          /* Hacks to determine whether current url matches the Link's path */
          let currentPath = String.concat("/", url.path);
          switch (currentPath) {
          | "" =>
            self.send(ChangeRouteStatus("/" == path ? Active : Inactive))
          | _ =>
            self.send(
              ChangeRouteStatus(currentPath == path ? Active : Inactive),
            )
          };
        }),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  render: self =>
    switch (self.state.routeStatus) {
    | Active => <b> children </b>
    | Inactive => <a href=path onClick=(handleClick(path))> children </a>
    },
};