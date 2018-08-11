let component = ReasonReact.statelessComponent("AnniversaryItem");

let make =
    (
      ~anniversary: Anniversary.t,
      ~isPast: bool,
      ~isToday: bool,
      ~showShare: bool,
      ~setShowShare: bool => unit,
      _children,
    ) => {
  ...component,
  render: _self => {
    let isToday = DateFns.isToday(anniversary.date);
    let toggleShowShare = _e => setShowShare(! showShare);
    <div className="AnniversaryItem">
      <div
        className=(
          "AnniversaryItem__display "
          ++ (showShare ? "AnniversaryItem__display--hidden" : "")
        )
        onClick=toggleShowShare>
        <Icon anniversary />
        <div className="AnniversaryItem__description">
          <Description anniversary isPast isToday />
        </div>
      </div>
      {
        let text = Description.text(anniversary, isPast, isToday);
        let url = "http://interesting-anniversaries.com";
        <div
          className=(
            "AnniversaryItem__share "
            ++ (showShare ? "AnniversaryItem__share--shown" : "")
          )>
          <TwitterButton text url onClick=toggleShowShare />
          <FacebookButton text url onClick=toggleShowShare />
          <a
            className="Button AnniversaryItem__shareButton AnniversaryItem__shareButton--close"
            onClick=toggleShowShare>
            (ReasonReact.string("Close"))
          </a>
        </div>;
      }
    </div>;
  },
};