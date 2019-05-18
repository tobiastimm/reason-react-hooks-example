module NavStyles = {
  open Css;
  let nav =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      background(hex(Theme.colorCyan)),
      color(hex(Theme.colorBg)),
      position(`fixed),
      top(rem(0.)),
      left(rem(0.)),
      width(pct(100.)),
      height(rem(Theme.navHeight)),
      zIndex(9),
      `transition(
        "background 250ms ease-in-out 0s,
        box-shadow 250ms ease-in-out 0s",
      ),
      `shadow("0 3px 6px rgba(0,0,0,0.16), 0 3px 6px rgba(0,0,0,0.23);"),
    ]);
  let menu =
    style([
      display(`flex),
      flexDirection(`row),
      flexWrap(`nowrap),
      justifyContent(`flexEnd),
      alignItems(`center),
      height(pct(100.)),
      alignSelf(`flexEnd),
    ]);
  let brand =
    style([
      marginLeft(rem(1.5)),
      display(`flex),
      justifyContent(`center),
      alignItems(`center),
      height(pct(100.)),
      width(rem(15.)),
    ]);
  let item =
    style([
      position(`relative),
      display(`flex),
      justifyContent(`center),
      alignItems(`center),
      boxSizing(`borderBox),
      height(pct(100.)),
      marginRight(rem(1.5)),
      padding2(~v=`zero, ~h=rem(1.)),
      cursor(`pointer),
      before([
        unsafe("content", ""),
        position(`absolute),
        left(pct(50.)),
        bottom(pct(20.)),
        width(pct(85.)),
        height(px(2)),
        backgroundColor(hex(Theme.colorBg)),
        unsafe("transform-origin", "center"),
        unsafe("transform", "translate(-50%, 0) scaleX(0)"),
        unsafe("transition", "transform 0.3s ease-in-out"),
      ]),
      hover([
        before([unsafe("transform", "translate(-50%, 0) scaleX(1)")]),
      ]),
    ]);
};

[@react.component]
let make = () =>
  <nav className=NavStyles.nav>
    <div className=NavStyles.brand>
      <h2> {React.string("Recipe Book")} </h2>
    </div>
    <div className=NavStyles.menu>
      <a className=NavStyles.item> {React.string("Recipes")} </a>
      <a className=NavStyles.item> {React.string("Shopping-List")} </a>
    </div>
  </nav>;