type state = {sharingIndex: option(int)};

type action =
  | SetSharingIndex(int)
  | ClearSharingIndex;

let component = ReasonReact.reducerComponent("AnniversaryList");

let make = (~anniversaries: array(Anniversary.t), ~isPast: bool, _children) => {
  ...component,
  initialState: () => {sharingIndex: Some(0)},
  reducer: (action, state) =>
    switch (action) {
    | SetSharingIndex(index) =>
      ReasonReact.Update({sharingIndex: Some(index)})
    | ClearSharingIndex => ReasonReact.Update({sharingIndex: None})
    },
  render: self => {
    let iterator = anniversaries |> Iterator.fromArray;
    /* |> Iterator.firstChunk((a, b) =>
         DateFns.isSameDay(a.Anniversary.date, b.Anniversary.date)
       ); */
    <div className="AnniversaryList RowFull">
      (
        iterator
        |> Iterator.toArray
        |> Array.mapi((index, ann: Anniversary.t) =>
             <div key=(string_of_int(index))>
               <AnniversaryItem
                 anniversary=ann
                 isPast
                 isToday=(DateFns.isToday(ann.date))
                 showShare={
                             let sharingIndex =
                               self.state.sharingIndex
                               |> Utils.optionDefault(-1);
                             sharingIndex === index;
                           }
                 setShowShare=(
                   showShare =>
                     if (showShare) {
                       self.send(SetSharingIndex(index));
                     } else {
                       self.send(ClearSharingIndex);
                     }
                 )
               />
             </div>
           )
        |> ReasonReact.array
      )
    </div>;
  },
};

type foo('state) =
  | Foo('state)
  | Bar
  | Baz;