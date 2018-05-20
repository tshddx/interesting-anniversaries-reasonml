let component = ReasonReact.statelessComponent("AboutPage");

let make = (~name, _children) => {
  ...component,
  render: _self =>
    <div>
      <h2> (ReasonReact.string("About")) </h2>
      <p> (ReasonReact.string(name)) </p>
    </div>,
};