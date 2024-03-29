module View = {
  module Styles = {
    open Css;

    /*
      Implementation of View that mock react-native
       https://github.com/necolas/react-native-web/blob/master/packages/react-native-web/src/exports/View/index.js#L69
     */

    let default =
      style([
        alignItems(`stretch),
        borderWidth(zero),
        borderStyle(`solid),
        boxSizing(`borderBox),
        display(`flex),
        flexDirection(`column),
        flexGrow(0.),
        flexShrink(0),
        margin(zero),
        padding(zero),
        position(`relative),
        minHeight(zero),
        minWidth(zero),
        userSelect(`none),
        position(`relative),
      ]);
  };

  let component = ReasonReact.statelessComponent("View");

  let make =
      (
        ~className="",
        ~onScroll=?,
        ~onPress=?,
        ~onKeyDown=?,
        ~onMouseEnter=?,
        ~onMouseLeave=?,
        ~onBlur=?,
        ~tabIndex=?,
        ~ref=?,
        children,
      ) => {
    ...component,

    render: _self =>
      <div
        className={Css.merge([Styles.default, className])}
        ?onScroll
        ?tabIndex
        ?onBlur
        onClick=?onPress
        ?onMouseEnter
        ?onMouseLeave
        ?onKeyDown
        ?ref>
        ...children
      </div>,
  };
};

module Row = {
  module Style = {
    let default = Css.(style([flexDirection(`row)]));
  };
  let component = ReasonReact.statelessComponent("Row");
  let make =
      (
        ~tabIndex=?,
        ~onKeyDown=?,
        ~className="",
        ~onScroll=?,
        ~onPress=?,
        ~onMouseEnter=?,
        ~onMouseLeave=?,
        children,
      ) => {
    ...component,
    render: _self =>
      <View
        className={Css.merge([Style.default, className])}
        ?tabIndex
        ?onKeyDown
        ?onScroll
        ?onPress
        ?onMouseEnter
        ?onMouseLeave>
        ...children
      </View>,
  };
};

module TouchableOpacity = {
  type cursorType = [ | `enabled | `disabled];

  type containerType = [ | `view | `row];

  module Styles = {
    open Css;

    let createContainerStyle = (mode, activeOpacity, hoverOpacity) =>
      switch (mode, activeOpacity, hoverOpacity) {
      | (`disabled, _, _) => style([hover([cursor(`notAllowed)])])
      | (`enabled, activeOpacityValue, hoverOpacityValue) =>
        style([
          active([
            opacity(activeOpacityValue),
            transition(~duration=0, "opacity"),
          ]),
          hover([
            opacity(hoverOpacityValue),
            transition(~duration=0, "opacity"),
            cursor(`pointer),
          ]),
        ])
      };
  };

  let component = ReasonReact.statelessComponent("TouchableOpacity");

  let make =
      (
        ~className="",
        ~onPress=?,
        ~onKeyDown=?,
        ~hoverOpacity=0.85,
        ~activeOpacity=0.5,
        ~mode=`enabled,
        ~tabIndex=?,
        ~containerType=`view,
        children,
      ) => {
    ...component,
    render: _self => {
      let resolvedStyle =
        Css.merge([
          Styles.createContainerStyle(mode, activeOpacity, hoverOpacity),
          className,
        ]);

      switch (containerType) {
      | `view =>
        <View ?onKeyDown className=resolvedStyle ?onPress ?tabIndex>
          ...children
        </View>
      | `row =>
        <Row ?onKeyDown className=resolvedStyle ?onPress ?tabIndex>
          ...children
        </Row>
      };
    },
  };
};

module Text = {
  module Styles = {
    let default =
      Css.(
        style([
          fontSize(`px(14)),
          fontFamily("Arial"),
          overflow(`hidden),
          textOverflow(`ellipsis),
          whiteSpace(`nowrap),
        ])
      );
  };
  let component = ReasonReact.statelessComponent("Text");

  let make = (~className="", ~value, _children) => {
    ...component,
    render: _self => {
      <p className={Css.merge([Styles.default, className])}>
        value->ReasonReact.string
      </p>;
    },
  };
};