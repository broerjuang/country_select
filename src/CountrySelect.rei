type state = {isOpen: bool};
type action =
  | ToggleDropdown;
let component:
  ReasonReact.componentSpec(
    state,
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    action,
  );
let make:
  (
    ~className: string=?,
    ~onSelect: 'a => 'b,
    ~selectedValue: option(string),
    ~options: array({.. "label": 'a}),
    'c
  ) =>
  ReasonReact.componentSpec(
    state,
    state,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    action,
  );