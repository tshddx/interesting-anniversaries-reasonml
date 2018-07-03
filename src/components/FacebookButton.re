let component = ReasonReact.statelessComponent("FacebookButton");

let make = (~text, ~url, ~onClick, _children) => {
  ...component,
  render: _self => {
    let href = {j|https://www.facebook.com/sharer/sharer.php?u=$(url)&quote=$(text)|j};
    <a
      href
      className="Button AnniversaryItem__shareButton AnniversaryItem__shareButton--facebook"
      target="_blank"
      onClick>
      (ReasonReact.string("Facebook"))
    </a>;
  },
};