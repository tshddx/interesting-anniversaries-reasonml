let component = ReasonReact.statelessComponent("NotFoundPage");

let make = _children => {
  ...component,
  render: _self =>
    <div> <h2> <i> (ReasonReact.string("Page not found")) </i> </h2> </div>,
};