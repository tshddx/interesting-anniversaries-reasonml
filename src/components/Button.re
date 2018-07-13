open Color;

let component = ReasonReact.statelessComponent("Button");

let make = (~color: Color.t, ~add: (float, Color.t) => Color.t, children) => {
  ...component,
  render: _self => {
    /* let color = color |> addHSLuv(~s=0.1); */
    /* let other = color |> darken(~by=0.1); */
    let other = color |> add(0.3);
    let other = color |> add(-0.05);
    let border = "1px solid " ++ toHex(other);
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
    <div
      style=(
        ReactDOMRe.Style.make(
          ~margin="0px",
          ~backgroundColor=toHex(color),
          ~borderRight=border,
          ~borderBottom=border,
          ~flexGrow="1",
          (),
        )
      )
    />;
  },
};