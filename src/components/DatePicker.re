type state = {
  year: option(int),
  month: option(int),
  day: option(int),
};

let initial_state = {year: Some(1995), month: Some(1), day: Some(1)};

let initial_state = {year: Some(1987), month: Some(7), day: Some(5)};

let initial_state = {year: None, month: None, day: None};

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
    Js.Date.makeWithYM(float_of_int(y), float_of_int(m), ())
    |> DateFns.getDaysInMonth
    |> int_of_float
  | (None, Some(m)) =>
    Js.Date.makeWithYM(2001.0, float_of_int(m), ())
    |> DateFns.getDaysInMonth
    |> int_of_float
  | _ => 31
  };

let constrainDay = state =>
  /* Js.log(daysInMonth(state)); */
  switch (state.day) {
  | Some(day') =>
    Js.log2("some day", day');
    {...state, day: Some(min(daysInMonth(state), day'))};
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
  didMount: self => onDateChange(getDate(self.state)),
  didUpdate: ({newSelf}) => onDateChange(getDate(newSelf.state)),
  render: self => {
    let {year, month, day} = self.state;
    let daysInMonth = daysInMonth(self.state);
    let thisYear = Js.Date.make() |> DateFns.getYear |> int_of_float;
    let yearOptions =
      Array.init(
        200,
        i => {
          let s = string_of_int(thisYear - i);
          (s, s);
        },
      );
    let monthOptions = [|
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
    let dayOptions =
      Array.init(
        daysInMonth,
        i => {
          let s = string_of_int(i + 1);
          (s, s);
        },
      );
    let yearValue = year |> Utils.optionMap(string_of_int);
    let monthValue = month |> Utils.optionMap(string_of_int);
    let dayValue = day |> Utils.optionMap(string_of_int);
    let color = Color.fromHSLuv(0.8, 0.6, 0.95);
    /* let color2 = color |> Color.addHSLuv(~h=0.34);
       let color3 = color2 |> Color.addHSLuv(~h=0.34); */
    <div className="DatePicker">
      <div className="DatePicker__field">
        <DatePickerSelect
          className="DatePicker__month"
          options=monthOptions
          value=monthValue
          defaultLabel="Month"
          onChange=(
            value => self.send(SetMonth(Some(int_of_string(value))))
          )
        />
      </div>
      <div className="DatePicker__field">
        <DatePickerSelect
          className="DatePicker__day"
          options=dayOptions
          value=dayValue
          defaultLabel="Day"
          onChange=(value => self.send(SetDay(Some(int_of_string(value)))))
        />
      </div>
      <div className="DatePicker__field">
        <DatePickerSelect
          className="DatePicker__year"
          options=yearOptions
          value=yearValue
          defaultLabel="Year"
          onChange=(
            value => self.send(SetYear(Some(int_of_string(value))))
          )
        />
      </div>
    </div>;
  },
};