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
              )>
              <a
                href="https://twitter.com/intent/tweet?text=FOO&url=http://interesting-anniversaries.now.sh"
                className="Button AnniversaryItem__shareButton AnniversaryItem__shareButton--twitter"
                target="_blank"
                onClick=(
                  e => {
                    if (false) {
                      ReactEventRe.Mouse.stopPropagation(e);
                    };
                    toggleShowShare();
                    Js.log("twitter");
                  }
                )>
                (ReasonReact.string("Twitter"))
              </a>
              <a
                href="https://www.facebook.com/sharer/sharer.php?u=http%3A//example.com/foo&quote=FOO"
                target="_blank"
                className="Button AnniversaryItem__shareButton AnniversaryItem__shareButton--facebook"
                onClick=(
                  e => {
                    if (false) {
                      ReactEventRe.Mouse.stopPropagation(e);
                    };
                    toggleShowShare();
                    Js.log("facebook");
                  }
                )>
                (ReasonReact.string("Facebook"))
              </a>
              <button
                className="Button AnniversaryItem__shareButton AnniversaryItem__shareButton--cancel"
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