let component = ReasonReact.statelessComponent("TwitterButton");

let make = (~text, ~url, ~onClick, _children) => {
  ...component,
  render: _self => {
    let href = {j|https://twitter.com/intent/tweet?text=$(text)&url=$(url)|j};
    <a
      href
      className="Button AnniversaryItem__shareButton AnniversaryItem__shareButton--twitter"
      target="_blank"
      onClick>
      (ReasonReact.string("Twitter"))
    </a>;
  },
};