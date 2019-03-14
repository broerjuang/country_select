type state = {
  isOpen: bool,
  optionMap: Js.Dict.t(string),
};
type action =
  | ToggleDropdown
  | MapOption;

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
    ~onSelect: Js.Dict.key => 'a,
    ~withVirtualized: bool=?,
    ~selectedValue: option(string),
    ~options: array({
                ..
                "label": string,
                "value": Js.Dict.key,
              }),
    'b
  ) =>
  ReasonReact.componentSpec(
    state,
    state,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    action,
  );