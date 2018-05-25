[%bs.raw {|require('../../../src/Main.css')|}];

type route =
  | HomeRoute
  | AboutRoute
  | NoRoute;

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => HomeRoute
  | ["about"] => AboutRoute
  | _ => NoRoute
  };

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let component = ReasonReact.reducerComponent("Main");

let make = _children => {
  ...component,
  reducer,
  initialState: () => {route: HomeRoute},
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          self.send(ChangeRoute(url |> mapUrlToRoute))
        ),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  render: self =>
    <div>
      <h1> (ReasonReact.string("Interesting Anniversaries")) </h1>
      <menu>
        <li> <Link path="/"> ...(ReasonReact.string("Home")) </Link> </li>
        <li>
          <Link path="about"> ...(ReasonReact.string("About")) </Link>
        </li>
      </menu>
      <hr />
      <div>
        (
          switch (self.state.route) {
          | HomeRoute => <HomePage greeting="Hello!" />
          | AboutRoute => <AboutPage name="My name is Thomas Shaddox" />
          | NoRoute => <NotFoundPage />
          }
        )
      </div>
    </div>,
};