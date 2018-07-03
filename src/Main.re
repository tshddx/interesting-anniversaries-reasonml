[%bs.raw {|require('../../../src/Main.css')|}];

[%bs.raw {|require('../../../src/favicon.png')|}];

let s = ReasonReact.string;

let component = ReasonReact.statelessComponent("Main");

let make = _children => {
  ...component,
  render: self =>
    <div className="Main">
      <div className="Row Header">
        <div className="MaxWidth">
          <h1> (s("Interesting Anniversaries")) </h1>
        </div>
      </div>
      <div className="Row Main__routeHolder">
        <div className="MaxWidth"> <HomePage /> </div>
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