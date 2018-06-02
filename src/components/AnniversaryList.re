let component = ReasonReact.statelessComponent("AnniversaryList");

let make = (~anniversaries: array(Anniversary.t), ~isPast: bool, _children) => {
  ...component,
  render: _self =>
    <ul className="AnniversaryList">
      (
        anniversaries
        |> Array.mapi((index, ann: Anniversary.t) =>
             <li>
               <AnniversaryItem
                 key=(string_of_int(index))
                 anniversary=ann
                 isPast
               />
             </li>
           )
        |> ReasonReact.array
      )
    </ul>,
};