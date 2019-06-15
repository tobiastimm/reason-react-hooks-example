module Styles = {
  open Css;

  let fab =
    style([
      position(`fixed),
      bottom(rem(5.)),
      right(rem(5.)),
      width(rem(4.2)),
      height(rem(4.2)),
      border(`zero, `none, hex("333")),
      color(hex(Theme.colorBg)),
      backgroundColor(hex(Theme.colorPink)),
      textAlign(`center),
      borderRadius(pct(50.)),
      verticalAlign(`middle),
      cursor(`pointer),
      `shadow(
        "0px 1px 3px 0px rgba(0,0,0,0.2),0px 1px 1px 0px rgba(0,0,0,0.14),0px 2px 1px -1px rgba(0,0,0,0.12)",
      ),
    ]);
};

[@react.component]
let make = (~click) => {
  <button className=Styles.fab onClick=click>
    <FeatherIcons.Plus color="#fff" />
  </button>;
};