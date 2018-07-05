open Color;

let component = ReasonReact.statelessComponent("Button");

let make = (~color: Color.t, children) => {
  ...component,
  render: _self => {
    let color = color |> lighten(~by=0.1);
    let other = color |> darken(~by=0.2);
    <button
      className="Button"
      style=(
        ReactDOMRe.Style.make(
          ~margin="5px",
          ~backgroundColor=toHex(color),
          ~border="1px solid " ++ toHex(other),
          (),
        )
      )>
      (ReasonReact.string("button"))
    </button>;
  },
};