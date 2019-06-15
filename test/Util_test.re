open Jest;
open Expect;

describe("Util", () => {
  describe("contains", () => {
    test("should find the given item", () =>
      expect(Util.contains(~value="Test", ["bla", "blub", "Test"]))
      |> toBe(true)
    );

    test("should not find the given item", () =>
      expect(Util.contains(~value="HERO", ["bla", "blub", "Test"]))
      |> toBe(false)
    );
  });

  describe("replaceKey", () =>
    ()
  );
});