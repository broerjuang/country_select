(* Auto-generated from "country.atd" *)
              [@@@ocaml.warning "-27-32-35-39"]

type country = Country_t.country = { label: string; value: string }

type response = Country_t.response = { data: country list }

let write_country = (
  Atdgen_codec_runtime.Encode.make (fun (t : country) ->
    (
    Atdgen_codec_runtime.Encode.obj
      [
          Atdgen_codec_runtime.Encode.field
            (
            Atdgen_codec_runtime.Encode.string
            )
          ~name:"label"
          t.label
        ;
          Atdgen_codec_runtime.Encode.field
            (
            Atdgen_codec_runtime.Encode.string
            )
          ~name:"value"
          t.value
      ]
    )
  )
)
let read_country = (
  Atdgen_codec_runtime.Decode.make (fun json ->
    (
      ({
          label =
            Atdgen_codec_runtime.Decode.decode
            (
              Atdgen_codec_runtime.Decode.string
              |> Atdgen_codec_runtime.Decode.field "label"
            ) json;
          value =
            Atdgen_codec_runtime.Decode.decode
            (
              Atdgen_codec_runtime.Decode.string
              |> Atdgen_codec_runtime.Decode.field "value"
            ) json;
      } : country)
    )
  )
)
let write__1 = (
  Atdgen_codec_runtime.Encode.list (
    write_country
  )
)
let read__1 = (
  Atdgen_codec_runtime.Decode.list (
    read_country
  )
)
let write_response = (
  Atdgen_codec_runtime.Encode.make (fun (t : response) ->
    (
    Atdgen_codec_runtime.Encode.obj
      [
          Atdgen_codec_runtime.Encode.field
            (
            write__1
            )
          ~name:"data"
          t.data
      ]
    )
  )
)
let read_response = (
  Atdgen_codec_runtime.Decode.make (fun json ->
    (
      ({
          data =
            Atdgen_codec_runtime.Decode.decode
            (
              read__1
              |> Atdgen_codec_runtime.Decode.field "data"
            ) json;
      } : response)
    )
  )
)
