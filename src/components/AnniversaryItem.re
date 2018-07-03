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
    let date = anniversary.date |> Utils.df;
    let toggleShowShare = _e => {
      Js.log("toggle");
      setShowShare(! showShare);
    };
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
      (
        showShare ?
          {
            let html = {|
              <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
              |};
            <div
              className=(
                "AnniversaryItem__share "
                ++ (showShare ? "AnniversaryItem__share--shown" : "")
              )
              onClick=toggleShowShare>
              <button
                className="Button AnniversaryItem__shareButton"
                onClick=(
                  e => {
                    ReactEventRe.Mouse.stopPropagation(e);
                    Js.log("twitter");
                  }
                )>
                (ReasonReact.string("Twitter"))
              </button>
              <button
                className="Button AnniversaryItem__shareButton"
                onClick=(
                  e => {
                    ReactEventRe.Mouse.stopPropagation(e);
                    Js.log("facebook");
                  }
                )>
                (ReasonReact.string("Facebook"))
              </button>
              <button
                className="Button AnniversaryItem__shareButton"
                onClick=toggleShowShare>
                (ReasonReact.string("Cancel"))
              </button>
            </div>;
          } :
          ReasonReact.null
      )
    </div>;
  },
};