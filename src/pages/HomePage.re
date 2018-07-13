open Color;

type state = {
  birthday: option(Js.Date.t),
  anniversaries: option(AnniversaryGenerator.anniversaryList),
  beforeNow: int,
  sharing: option(Anniversary.t),
};

type action =
  | SetBirthday(option(Js.Date.t))
  | ShowMore
  | SetSharing(Anniversary.t)
  | ClearSharing;

let initialShowBeforeNow = 1000;

let initialShowBeforeNow = 0;

let showMore = 10;

let component = ReasonReact.reducerComponent("HomePage");

open Iterator;

let getAnniversaries = (birthday, beforeNow) =>
  birthday
  |> Utils.optionMap(birthday =>
       AnniversaryGenerator.get(birthday, Js.Date.make(), beforeNow)
     );

let make = _children => {
  ...component,
  initialState: () => {
    birthday: None,
    anniversaries: None,
    beforeNow: 0,
    sharing: None,
  },
  reducer: (action, state) =>
    switch (action) {
    | SetBirthday(birthday) =>
      ReasonReact.Update({
        birthday,
        anniversaries: getAnniversaries(birthday, initialShowBeforeNow),
        beforeNow: initialShowBeforeNow,
        sharing: None,
      })
    | ShowMore =>
      let beforeNow = state.beforeNow + showMore;
      ReasonReact.Update({
        ...state,
        anniversaries: getAnniversaries(state.birthday, beforeNow),
        beforeNow,
      });
    | SetSharing(ann) => ReasonReact.Update({...state, sharing: Some(ann)})
    | ClearSharing => ReasonReact.Update({...state, sharing: None})
    },
  /* shouldUpdate: ({oldSelf, newSelf}) =>
     oldSelf.state.birthday !== newSelf.state.birthday
     || oldSelf.state.sharing !== newSelf.state.sharing, */
  render: self => {
    let now = Js.Date.make();
    let anniversaries =
      switch (self.state.anniversaries) {
      | Some(anns) =>
        let past = anns.past;
        let shownPast = anns.shownPast;
        let future = anns.future;
        let colors =
          [|"d98fb9", "8ed98e", "ffffa8"|]
          |> Array.map(hexString =>
               hexString |> fromHexString |> Utils.optionGet
             );
        let baseColor = fromHSLuv(0.0, 1.0, 0.95);
        let res = 50;
        let rows = res;
        let perRow = res;
        let bases =
          Array.init(rows, i =>
            baseColor
            |> Color.addHSLuv(
                 ~h=float_of_int(i) *. 1.0 /. float_of_int(rows),
               )
          );
        let add = l => addHPLuv(~h=0.0, ~s=0.0, ~l);
        let add = l => addHSLuv(~h=0.0, ~s=0.0, ~l);
        <div className="Anniversaries">
          <div className="Colors2">
            (
              bases
              |> Array.map(base =>
                   <div className="Colors">
                     (
                       Array.init(
                         perRow,
                         i => {
                           let color =
                             base
                             |> darken(
                                  ~by=
                                    float_of_int(i)
                                    *. 0.0
                                    /. float_of_int(perRow),
                                );
                           <Button color add />;
                         },
                       )
                       |> ReasonReact.array
                     )
                   </div>
                 )
              |> ReasonReact.array
            )
          </div>
          (
            Array.length(past) > 0 ?
              <button
                className="Button PreviousButton"
                onClick=(_e => self.send(ShowMore))>
                (ReasonReact.string("See previous anniversaries"))
              </button> :
              ReasonReact.null
          )
          (
            Array.length(shownPast) > 0 ?
              <AnniversaryList
                anniversaries=shownPast
                isPast=true
                sharing=self.state.sharing
                setSharing=(sharing => self.send(SetSharing(sharing)))
                clearSharing=(() => self.send(ClearSharing))
              /> :
              ReasonReact.null
          )
          (Array.length(shownPast) > 0 ? <hr /> : ReasonReact.null)
          <AnniversaryList
            anniversaries=future
            isPast=false
            sharing=self.state.sharing
            setSharing=(sharing => self.send(SetSharing(sharing)))
            clearSharing=(() => self.send(ClearSharing))
          />
        </div>;
      | None => ReasonReact.null
      };
    <div>
      <h2> (ReasonReact.string("When's your birthday?")) </h2>
      <DatePicker onDateChange=(date => self.send(SetBirthday(date))) />
      anniversaries
    </div>;
  },
};