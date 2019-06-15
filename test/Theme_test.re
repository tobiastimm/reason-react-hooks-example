open Jest;
open Expect;

describe("Theme", () => {
  test("navHeight to be 5.", () =>
    expect(Theme.navHeight) |> toBe(5.)
  );
  test("colorBg to be 'eeeeee'", () =>
    expect(Theme.colorBg) |> toBe("eeeeee")
  );
});