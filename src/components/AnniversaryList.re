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
                 showShare=(
                   switch (sharing) {
                   | Some(sharing) =>
                     let eq2 = ann == sharing;
                     let eq3 = ann === sharing;
                     if (eq2) {
                       Js.log4("compare sharing", eq3, ann, sharing);
                     };
                     ann === sharing;
                   | None => false
                   }
                 )
                 setShowShare=(
                   showShare =>
                     if (showShare) {
                       Js.log("set sharing");
                       setSharing(ann);
                     } else {
                       Js.log("clear sharing");
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