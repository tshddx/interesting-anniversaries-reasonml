type state = {birthday: option(Js.Date.t)};

type action =
  | SetBirthday(option(Js.Date.t));

let component = ReasonReact.reducerComponent("HomePage");

open Iterator;

let make = (~greeting, _children) => {
  ...component,
  initialState: () => {birthday: None},
  reducer: (action, state) =>
    switch (action) {
    | SetBirthday(birthday) => ReasonReact.Update({...state, birthday})
    },
  render: self => {
    let now = Js.Date.make();
    /* let generators = InterestingNumber.generators;
       let cats =
         <div>
           (
             generators
             |> List.map(gen =>
                  gen()
                  |> take(5)
                  |> map((num: InterestingNumber.t) =>
                       <div>
                         (ReasonReact.string(num.category))
                         (ReasonReact.string(": "))
                         (ReasonReact.string(string_of_float(num.value)))
                       </div>
                     )
                  |> to_list
                  |> Array.of_list
                  |> ReasonReact.array
                )
             |> Array.of_list
             |> ReasonReact.array
           )
         </div>; */
    Js.log(self.state.birthday);
    let anniversaries =
      switch (self.state.birthday) {
      | Some(birthday) =>
        let dates = AnniversaryGenerator.generate(birthday, now);
        Js.log(List.length(dates));
        <div className="Anniversaries">
          <ul>
            (
              dates
              |> List.mapi((index, ann: Anniversary.t) =>
                   <li>
                     <AnniversaryItem
                       key=(string_of_int(index))
                       anniversary=ann
                     />
                   </li>
                 )
              |> Array.of_list
              |> ReasonReact.array
            )
          </ul>
        </div>;
      | None =>
        Js.log("no birthday");
        ReasonReact.null;
      };
    <div>
      <h2> (ReasonReact.string("What is your birthday?")) </h2>
      <DatePicker onDateChange=(date => self.send(SetBirthday(date))) />
      anniversaries
    </div>;
  },
};