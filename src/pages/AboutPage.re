let component = ReasonReact.statelessComponent("AboutPage");

let make = (~name, _children) => {
  ...component,
  render: _self =>
    <div>
      <p>
        (
          ReasonReact.string(
            "Interesting Anniversaries is a recreational coding exercise by ",
          )
        )
        <a href="https://twitter.com/baddox">
          (ReasonReact.string("Thomas Shaddox"))
        </a>
        (ReasonReact.string("."))
      </p>
      <p>
        (ReasonReact.string("The source code is on "))
        <a href="https://github.com/baddox/interesting-anniversaries-reasonml">
          (ReasonReact.string("GitHub"))
        </a>
        (ReasonReact.string("."))
      </p>
    </div>,
};