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
      | Achievement({emoji}) => ReasonReact.string(emoji)
      | CelestialDuration(_) => ReasonReact.string({js|☄️|js})
      };
    let extraClassName =
      switch (anniversary.source) {
      | InterestingNumber(_, number) =>
        number.category == "everyYear" ? "" : "Icon--default"
      | Achievement(_a) => ""
      | CelestialDuration(_) => ""
      };
    let className = "Icon " ++ extraClassName;
    <div className> icon </div>;
  },
};

let text = (anniversary: Anniversary.t) => {
  let icon =
    switch (anniversary.source) {
    | InterestingNumber(_, number) =>
      number.category == "everyYear" ? {js|🎂|js} : {js|🕒|js}
    | Achievement({emoji}) => emoji
    | CelestialDuration(_) => {js|☄️|js}
    };
  ();
};