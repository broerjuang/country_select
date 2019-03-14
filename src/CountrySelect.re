open Utils.Option;
open CoreUI;
open UIKit;

type state = {
  isOpen: bool,
  optionMap: Js.Dict.t(string),
};

type action =
  | ToggleDropdown
  | MapOption;

let component = ReasonReact.reducerComponent("State");

let make =
    (
      ~className=?,
      ~onSelect,
      ~selectedValue: option(string),
      ~options,
      _children,
    ) => {
  ...component,
  initialState: () => {isOpen: false, optionMap: Js.Dict.empty()},
  reducer: (action, state) => {
    switch (action) {
    | ToggleDropdown => ReasonReact.Update({...state, isOpen: !state.isOpen})
    | MapOption =>
      let dict =
        Array.map(option_ => (option_##value, option_##label), options)
        |> Js.Dict.fromArray;
      ReasonReact.Update({...state, optionMap: dict});
    };
  },
  didMount: self => {
    // I put map option tp map option with correspondong string, so we'll not creating new dictionary for each render
    self.send(
      MapOption,
    );
  },
  render: ({state, send}) => {
    // Since the input is option(string), mapping to selectedValue and look the current value of dict
    let maybeValue = selectedValue >>= Js.Dict.get(state.optionMap);

    <View>
      <Trigger
        onPress={_ => send(ToggleDropdown)}
        isOpen={state.isOpen}
        selectedValue={maybeValue |? "Select Country"}
      />
      <ViewIf test={state.isOpen}>
        <Cover onClose={_ => send(ToggleDropdown)} />
        <Dropdown
          ?className
          selectedValue=?maybeValue
          onChange={option_ => {
            onSelect(option_##value);
            send(ToggleDropdown);
          }}
          options
        />
      </ViewIf>
    </View>;
  },
};