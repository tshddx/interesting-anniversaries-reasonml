let component = ReasonReact.statelessComponent("TwitterButton");

let make = (~onClick, _children) => {
  ...component,
  render: _self => {
    let url = "https://twitter.com/intent/tweet?text=FOO&url=http://interesting-anniversaries.now.sh";
    <a
      href=url
      className="Button AnniversaryItem__shareButton AnniversaryItem__shareButton--twitter"
      target="_blank"
      onClick>
      (ReasonReact.string("Twitter"))
    </a>;
  },
};