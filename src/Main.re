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

let s = ReasonReact.string;

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
    <div className="Main">
      <div className="Row Header">
        <div className="MaxWidth">
          <h1> (s("Interesting Anniversaries")) </h1>
        </div>
      </div>
      <div className="Row Main__routeHolder">
        <div className="MaxWidth">
          (
            switch (self.state.route) {
            | HomeRoute => <HomePage greeting="Hello!" />
            | AboutRoute => <AboutPage name="My name is Thomas Shaddox" />
            | NoRoute => <NotFoundPage />
            }
          )
        </div>
      </div>
      <div className="Row Footer">
        <div className="MaxWidth">
          <p>
            (
              s(
                "Interesting Anniversaries is a recreational coding exercise by ",
              )
            )
            <a href="https://twitter.com/baddox"> (s("Thomas Shaddox")) </a>
            (s(". "))
            (s("This site doesn't transmit or store any data. "))
            (s("The source code and more information is on "))
            <a
              href="https://github.com/baddox/interesting-anniversaries-reasonml">
              (s("GitHub"))
            </a>
            (s("."))
          </p>
        </div>
      </div>
    </div>,
};