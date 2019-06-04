module Styles = {
  open Css;

  let fab =
    style([
      position(`absolute),
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
    ]);
};

[@react.component]
let make = (~click) => {
  <button className=Styles.fab onClick=click>
    <FeatherIcons.Plus color="#fff" />
  </button>;
};