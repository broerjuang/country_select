open Utils.Option;
open CoreUI;
open UIKit;

type state = {isOpen: bool};

type action =
  | ToggleDropdown;

let component = ReasonReact.reducerComponent("State");

let make = (~className=?, ~onSelect, ~selectedValue, ~options, _children) => {
  ...component,
  initialState: () => {isOpen: false},
  reducer: (action, state) => {
    switch (action) {
    | ToggleDropdown => ReasonReact.Update({isOpen: !state.isOpen})
    };
  },
  render: ({state, send}) => {
    <View>
      <Trigger
        onPress={_ => send(ToggleDropdown)}
        isOpen={state.isOpen}
        selectedValue={selectedValue |? "Select Country"}
      />
      <ViewIf test={state.isOpen}>
        <Cover onClose={_ => send(ToggleDropdown)} />
        <Dropdown
          ?className
          ?selectedValue
          onChange={value => {
            onSelect(value##label);
            send(ToggleDropdown);
          }}
          options
        />
      </ViewIf>
    </View>;
  },
};