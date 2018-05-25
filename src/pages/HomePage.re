/* State declaration */
type state = {
  count: int,
  show: bool,
};

/* Action declaration */
type action =
  | Click
  | Toggle;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("HomePage");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~greeting, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {count: 0, show: true},
  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Click => ReasonReact.Update({...state, count: state.count + 1})
    | Toggle => ReasonReact.Update({...state, show: ! state.show})
    },
  render: self => {
    let now = Js.Date.make();
    let birthday = Js.Date.makeWithYMD(1987.0, 7.0, 5.0, ());
    let future = DateFns.addWeeks(1.0, now);
    let s = DateFns.distanceInWords(future, now);
    let dates = AnniversaryGenerator.generate(birthday, now);
    <div>
      (
        dates
        |> List.map((ann: Anniversary.t) =>
             <li>
               (ReasonReact.string("On "))
               (ReasonReact.string(DateFns.format("MMMM D, YYYY", ann.date)))
               (ReasonReact.string(" you will be "))
               (
                 ReasonReact.string(CommaNumber.commaNumber(ann.number.value))
               )
               (ReasonReact.string(" "))
               (
                 ReasonReact.string(
                   switch (ann.number.description) {
                   | Some(description) => {j|($description) |j}
                   | None => ""
                   },
                 )
               )
               (ReasonReact.string(ann.units))
               (ReasonReact.string(" old!"))
             </li>
           )
        |> Array.of_list
        |> ReasonReact.array
      )
    </div>;
  },
};