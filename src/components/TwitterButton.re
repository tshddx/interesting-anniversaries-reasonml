let component = ReasonReact.statelessComponent("TwitterButton");

let make = _children => {
  ...component,
  didMount: _self => [%bs.raw {| twttr.widgets.load() |}],
  render: _self =>
    ReasonReact.cloneElement(
      <a
        href="https://twitter.com/share?ref_src=twsrc%5Etfw"
        className="twitter-share-button">
        (ReasonReact.string("Tweet"))
      </a>,
      ~props={
        "data-size": "large",
        "data-text": "foo",
        "data-url": "http://example.com/foo",
        "data-show-count": "false",
      },
      [||],
    ),
};