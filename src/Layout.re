module GlobalStyles = {
  open Css;
  global("html", [fontSize(px(10))]);
  global("html, body, #root", [height(pct(100.)), boxSizing(`borderBox)]);
  global(
    "*,
          *:before,
          *:after ",
    [boxSizing(`inherit_)],
  );
  global(
    "body",
    [
      padding(zero),
      margin(zero),
      fontSize(rem(1.5)),
      color(hex(Theme.colorText)),
      background(hex(Theme.colorBg)),
      lineHeight(rem(2.)),
      fontFamily(
        "-apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto,
              Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue',
              sans-serif",
      ),
      minHeight(pct(100.)),
    ],
  );
  global("a", [textDecoration(`none)]);
};

[@react.component]
let make = (~children) => <> children </>;