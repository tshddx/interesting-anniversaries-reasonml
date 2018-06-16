let component = ReasonReact.statelessComponent("AnniversaryItem");

let make = (~anniversary: Anniversary.t, ~isPast: bool, _children) => {
  ...component,
  render: _self =>
    switch (anniversary.source) {
    | InterestingNumber(unit, number) =>
      <span>
        <span className="AnniversaryItem__emoji">
          (
            ReasonReact.string(
              number.category == "everyYear" ? {js|🎂|js} : {js|🔢|js},
            )
          )
        </span>
        <span className="AnniversaryItem__sentence">
          (ReasonReact.string("On "))
          (ReasonReact.string(anniversary.date |> Utils.df))
          (ReasonReact.string(isPast ? " you were " : " you will be "))
          <b>
            (ReasonReact.string(CommaNumber.commaNumber(number.value)))
            (ReasonReact.string(" "))
            (
              ReasonReact.string(
                switch (number.description) {
                | Some(description) => {j|($description) |j}
                | None => ""
                },
              )
            )
            (ReasonReact.string(unit))
          </b>
          (ReasonReact.string(" old!"))
        </span>
      </span>
    | Achievement(achievement) =>
      <span>
        <span className="AnniversaryItem__emoji">
          (ReasonReact.string({js|🏆|js}))
        </span>
        <span className="AnniversaryItem__sentence">
          (ReasonReact.string({|On |}))
          (ReasonReact.string(anniversary.date |> Utils.df))
          (
            ReasonReact.string(
              isPast ?
                " you were the same age as " : " you will be the same age as ",
            )
          )
          <b> (ReasonReact.string(achievement.name)) </b>
          (ReasonReact.string(" when "))
          (ReasonReact.string(achievement.achievement))
          (ReasonReact.string("!"))
        </span>
      </span>
    | CelestialDuration(celestialDuration) =>
      <span>
        <span className="AnniversaryItem__emoji">
          (ReasonReact.string({js|🌌|js}))
        </span>
        <span className="AnniversaryItem__sentence">
          (ReasonReact.string({|On |}))
          (ReasonReact.string(celestialDuration.date |> Utils.df))
          (ReasonReact.string(isPast ? " you were " : " you will be "))
          (ReasonReact.string(string_of_int(celestialDuration.number)))
          (ReasonReact.string(" years old in "))
          <b> (ReasonReact.string(celestialDuration.name)) </b>
          (ReasonReact.string(" years!"))
          (ReasonReact.string("!"))
        </span>
      </span>
    },
};