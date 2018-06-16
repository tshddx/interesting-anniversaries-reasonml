let component = ReasonReact.statelessComponent("AnniversaryItem");

let make = (~anniversary: Anniversary.t, ~isPast: bool, _children) => {
  ...component,
  render: _self =>
    switch (anniversary.source) {
    | InterestingNumber(unit, number) =>
      <span>
        (ReasonReact.string({js|🔢|js}))
        (ReasonReact.string("On "))
        (ReasonReact.string(anniversary.date |> Utils.df))
        (ReasonReact.string(isPast ? " you were " : " you will be "))
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
        (ReasonReact.string(" old!"))
      </span>
    | Achievement(achievement) =>
      <span>
        (ReasonReact.string({js|🏆|js}))
        (ReasonReact.string({| On |}))
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
    },
};