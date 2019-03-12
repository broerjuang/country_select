let component = ReasonReact.statelessComponent("Hello");

let make = _children => {
  ...component,
  render: _self => {
    ReasonReact.string("Hello world");
  },
};