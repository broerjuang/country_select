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
      ]);
  };

  let component = ReasonReact.statelessComponent("View");

  let make =
      (
        ~className="",
        ~onScroll=?,
        ~onPress=?,
        ~onMouseEnter=?,
        ~onMouseLeave=?,
        ~onBlur=?,
        ~tabIndex=?,
        ~ref=?,
        ~onKeyDown=?,
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
        ?onScroll
        ?onPress
        ?onMouseEnter
        ?onMouseLeave>
        ...children
      </View>,
  };
};