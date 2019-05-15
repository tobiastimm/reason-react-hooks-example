module NavStyles = {
  open Css;
  let nav =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      background(hex(Theme.colorHighlight)),
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
      margin(`zero),
      display(`flex),
      justifyContent(`center),
      alignItems(`center),
      height(pct(100.)),
      width(rem(7.)),
      padding2(~v=rem(0.), ~h=rem(1.)),
    ]);
  let item =
    style([
      display(`flex),
      justifyContent(`center),
      alignItems(`center),
      boxSizing(`borderBox),
      height(pct(100.)),
      padding2(~v=`zero, ~h=rem(1.)),
      cursor(`pointer),
      hover([
        color(hex(Theme.colorBg)),
        `transition("color 250ms ease-in-out 0s"),
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