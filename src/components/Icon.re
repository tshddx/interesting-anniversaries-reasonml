let component = ReasonReact.statelessComponent("Icon");

let make = (~anniversary: Anniversary.t, _children) => {
  ...component,
  render: _self => {
    let icon =
      switch (anniversary.source) {
      | InterestingNumber(_, number) =>
        number.category == "everyYear" ? {js|🎂|js} : {js|🔢|js}
      | Achievement(_) => {js|🏆|js}
      | CelestialDuration(_) => {js|☄️|js}
      };
    <div className="AnniversaryItem__emoji">
      (ReasonReact.string(icon))
    </div>;
  },
};