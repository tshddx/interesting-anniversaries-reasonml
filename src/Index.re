[%bs.raw {|require('../../../src/index.html')|}];

ReactDOMRe.renderToElementWithId(<Main />, "main");

/* Initial URL sync, courtesy of
   https://medium.com/@Hehk/routing-in-reasonreact-d512fdc81b63 */
ReasonReact.Router.push("");