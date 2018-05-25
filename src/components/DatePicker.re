type state = {
  year: option(int),
  month: option(int),
  day: option(int),
};

let initial_state = {year: None, month: None, day: None};

let initial_state = {year: Some(1987), month: Some(7), day: Some(5)};

type action =
  | SetYear(option(int))
  | SetMonth(option(int))
  | SetDay(option(int));

let getDate = ({year, month, day}) =>
  switch (year, month, day) {
  | (Some(y), Some(m), Some(d)) =>
    Some(
      Js.Date.makeWithYMD(
        float_of_int(y),
        float_of_int(m),
        float_of_int(d),
        (),
      ),
    )
  | _ => None
  };

let daysInMonth = ({year, month}) =>
  switch (year, month) {
  | (Some(y), Some(m)) =>
    Some(
      Js.Date.makeWithYM(float_of_int(y), float_of_int(m), ())
      |> DateFns.getDaysInMonth
      |> int_of_float,
    )
  | _ => None
  };

let constrainDay = state =>
  switch (daysInMonth(state), state.day) {
  | (Some(days), Some(day)) => {...state, day: Some(min(days, day))}
  | _ => state
  };

let reducer = (action, state) =>
  switch (action) {
  | SetYear(year) => ReasonReact.Update({...state, year} |> constrainDay)
  | SetMonth(month) => ReasonReact.Update({...state, month} |> constrainDay)
  | SetDay(day) => ReasonReact.Update({...state, day} |> constrainDay)
  };

let getValue = event => ReactDOMRe.domElementToObj(
                          ReactEventRe.Form.target(event),
                        )##value;

let getInt = event =>
  switch (getValue(event)) {
  | "" => None
  | v => Some(int_of_string(v))
  };

let component = ReasonReact.reducerComponent("DatePicker");

let make = (~onDateChange: option(Js.Date.t) => unit, _children) => {
  ...component,
  initialState: () => initial_state,
  reducer,
  shouldUpdate: ({oldSelf, newSelf}) => oldSelf.state != newSelf.state,
  render: self => {
    onDateChange(getDate(self.state));
    let {year, month, day} = self.state;
    let days_in_month = daysInMonth(self.state);
    let thisYear = Js.Date.make() |> DateFns.getYear |> int_of_float;
    let years =
      Array.append(
        [|""|],
        Array.init(200, i => string_of_int(thisYear - i)),
      );
    let months = [|
      ("", ""),
      ("0", "January"),
      ("1", "February"),
      ("2", "March"),
      ("3", "April"),
      ("4", "May"),
      ("5", "June"),
      ("6", "July"),
      ("7", "August"),
      ("8", "September"),
      ("9", "October"),
      ("10", "November"),
      ("11", "December"),
    |];
    let days =
      switch (days_in_month) {
      | Some(dayCount) =>
        Array.append(
          [|""|],
          Array.init(dayCount, i => string_of_int(i + 1)),
        )
      | _ => [|""|]
      };
    let year_value =
      switch (year) {
      | Some(year) => string_of_int(year)
      | None => ""
      };
    let month_value =
      switch (month) {
      | Some(month) => string_of_int(month)
      | None => ""
      };
    let day_value =
      switch (day) {
      | Some(day) => string_of_int(day)
      | None => ""
      };
    <div className="DatePicker">
      <div className="DatePicker__field">
        (ReasonReact.string("Year:"))
        <br />
        <select
          value=year_value
          onChange=(event => self.send(SetYear(getInt(event))))>
          (
            years
            |> Array.map(year =>
                 <option value=year> (ReasonReact.string(year)) </option>
               )
            |> ReasonReact.array
          )
        </select>
      </div>
      <div className="DatePicker__field">
        (ReasonReact.string("Month:"))
        <br />
        <select
          value=month_value
          onChange=(event => self.send(SetMonth(getInt(event))))>
          (
            months
            |> Array.map(((value, month)) =>
                 <option value> (ReasonReact.string(month)) </option>
               )
            |> ReasonReact.array
          )
        </select>
      </div>
      <div className="DatePicker__field">
        (ReasonReact.string("Day:"))
        <br />
        <select
          value=day_value
          disabled=(
            switch (days_in_month) {
            | Some(_) => false
            | None => true
            }
          )
          onChange=(event => self.send(SetDay(getInt(event))))>
          (
            days
            |> Array.map(i =>
                 <option value=i> (ReasonReact.string(i)) </option>
               )
            |> ReasonReact.array
          )
        </select>
      </div>
    </div>;
  },
};