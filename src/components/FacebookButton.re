let component = ReasonReact.statelessComponent("FacebookButton");

let make = (~onClick, _children) => {
  ...component,
  render: _self => {
    let url = "https://www.facebook.com/sharer/sharer.php?u=http%3A//example.com/foo&quote=FOO";
    <a
      href=url
      className="Button AnniversaryItem__shareButton AnniversaryItem__shareButton--facebook"
      target="_blank"
      onClick>
      (ReasonReact.string("Facebook"))
    </a>;
  },
};