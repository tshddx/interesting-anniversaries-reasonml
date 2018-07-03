let component = ReasonReact.statelessComponent("Icon");

let make = (~anniversary: Anniversary.t, _children) => {
  ...component,
  render: _self => {
    let icon =
      switch (anniversary.source) {
      | InterestingNumber(_, number) =>
        let emoji =
          number.category == "everyYear" ? {js|🎂|js} : {js|🕒|js};
        ReasonReact.string(emoji);
      | Achievement({icon}) => icon
      | CelestialDuration(_) => ReasonReact.string({js|☄️|js})
      };
    let extraClassName =
      switch (anniversary.source) {
      | InterestingNumber(_, number) =>
        number.category == "everyYear" ? "" : "Icon--default"
      | Achievement({icon}) => ""
      | CelestialDuration(_) => ""
      };
    let className = "Icon " ++ extraClassName;
    <div className> icon </div>;
  },
};