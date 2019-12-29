open Cmdliner;
open Spin;

let run =
    (~template: option(string), ~path: option(string), ~useDefaults, ()) => {
  let path = Option.value(path, ~default=".");
  let source =
    Option.map(template, Source.ofString)
    |> Option.value(
         ~default=Source.Git("https://github.com/tmattio/spin-minimal.git"),
       );
  Template.generate(source, path, ~useDefaults);
  Lwt.return();
};

let cmd = {
  let doc = "Create a new ReasonML/Ocaml project from a template";

  let template = {
    let doc = "The template to use to generate the project. Can be the name of an official template or a git repository.\nDefaults to the minimal official template.";
    Arg.(
      value & pos(0, some(string), None) & info([], ~docv="TEMPLATE", ~doc)
    );
  };

  let path = {
    let doc = "The path of the generated project.\nLeave empty to put files into current directory by default.";
    Arg.(value & pos(1, some(string), None) & info([], ~docv="PATH", ~doc));
  };

  let useDefaults = {
    let doc = "Use default values for the configuration. The user will be prompted only for configuration that don't have a default value";
    Arg.(value & flag & info(["default"], ~doc));
  };

  let runCommand = (template, path, useDefaults) =>
    run(~template, ~path, ~useDefaults) |> Errors.handleErrors |> Lwt_main.run;

  (
    Term.(const(runCommand) $ template $ path $ useDefaults),
    Term.info(
      "new",
      ~doc,
      ~envs=Man.envs,
      ~version=Man.version,
      ~exits=Man.exits,
      ~man=Man.man,
      ~sdocs=Man.sdocs,
    ),
  );
};
