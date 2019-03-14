(* Auto-generated from "country.atd" *)
              [@@@ocaml.warning "-27-32-35-39"]

type country = Country_t.country = { label: string; value: string }

type response = Country_t.response = { data: country list }

val read_country :  country Atdgen_codec_runtime.Decode.t

val write_country :  country Atdgen_codec_runtime.Encode.t

val read_response :  response Atdgen_codec_runtime.Decode.t

val write_response :  response Atdgen_codec_runtime.Encode.t

