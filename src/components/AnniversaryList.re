let component = ReasonReact.statelessComponent("AnniversaryList");

let make =
    (
      ~anniversaries: array(Anniversary.t),
      ~isPast: bool,
      ~sharing: option(Anniversary.t),
      ~setSharing: Anniversary.t => unit,
      ~clearSharing: unit => unit,
      _children,
    ) => {
  ...component,
  render: self => {
    let iterator = anniversaries |> Iterator.fromArray;
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
                 showShare=(
                   switch (sharing) {
                   | Some(sharing) => ann === sharing
                   | None => false
                   }
                 )
                 setShowShare=(
                   showShare =>
                     if (showShare) {
                       setSharing(ann);
                     } else {
                       clearSharing();
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