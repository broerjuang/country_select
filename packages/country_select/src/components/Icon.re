module ChevronDown = {
  let component = ReasonReact.statelessComponent("ChevronDown");
  let make = _children => {
    ...component,
    render: _self => {
      <svg
        width="24"
        height="24"
        viewBox="0 0 24 24"
        focusable="false"
        role="presentation">
        <path
          d="M8.292 10.293a1.009 1.009 0 0 0 0 1.419l2.939 2.965c.218.215.5.322.779.322s.556-.107.769-.322l2.93-2.955a1.01 1.01 0 0 0 0-1.419.987.987 0 0 0-1.406 0l-2.298 2.317-2.307-2.327a.99.99 0 0 0-1.406 0z"
          fill="currentColor"
          fillRule="evenodd"
        />
      </svg>;
    },
  };
};

module Search = {
  let component = ReasonReact.statelessComponent("ChevronDown");
  let make = _children => {
    ...component,
    render: _self => {
      <svg
        width="24"
        height="24"
        viewBox="0 0 24 24"
        focusable="false"
        role="presentation">
        <path
          d="M16.436 15.085l3.94 4.01a1 1 0 0 1-1.425 1.402l-3.938-4.006a7.5 7.5 0 1 1 1.423-1.406zM10.5 16a5.5 5.5 0 1 0 0-11 5.5 5.5 0 0 0 0 11z"
          fill="currentColor"
          fillRule="evenodd"
        />
      </svg>;
    },
  };
};