let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`flexEnd,
          ~flex=2.5,
          ~padding=25.->dp,
          (),
        ),
      "bottom":
        style(
          ~justifyContent=`center,
          ~flex=1.,
          ~alignItems=`center,
          ~width=100.->pct,
          (),
        ),
      "txt":
        style(
          ~fontFamily="Montserrat-Regular",
          ~color="#fff",
          ~fontSize=22.,
          ~paddingTop=16.->dp,
          (),
        ),
      "txtArea":
        style(
          ~backgroundColor="white",
          ~fontFamily="Montserrat-Regular",
          ~width=100.->pct,
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~marginBottom=5.->dp,
          ~fontFamily="Montserrat-Bold",
          ~fontSize=20.,
          (),
        ),
      "signature":
        style(~width=150.->dp, ~height=90.->dp, ~alignSelf=`center, ()),
      "figure":
        style(~width=150.->dp, ~alignSelf=`center, ~height=50.->dp, ()),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  let (text, setText) = React.useState(() => "");

  let submit = _ => {
    let url = "https://api.mailgun.net/v3/sandbox569e8db6afe542a1829ebde3c140630f.mailgun.org/messages";
    open Js.Dict;
    let payload = empty();
    payload->set("from", Js.Json.string("Mailgun Sandbox"));
    payload->set("to", Js.Json.string("contato@marcosinacio.adv.br"));
    payload->set("subject", Js.Json.string("Contato Aplicativo"));
    payload->set("from", Js.Json.string({j|$text|j}));

    Js.Promise.(
      Fetch.(
        fetchWithInit(
          url,
          RequestInit.make(
            ~method_=Post,
            ~body=
              BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
            ~headers=
              HeadersInit.make({
                "Authorization": "Basic YXBpOjA0MTA4M2U0MmFiNWY3N2ZkMzEyN2I0NzE4MzZlNzI4LTQ2YWM2YjAwLTk5NzM0OWNj",
                "Content-Type": "multipart/form-data",
              }),
            (),
          ),
        )
      )
      |> then_(_ => {
           open ReactNative.ToastAndroid;
           showWithGravityAndOffset(
             "Email Enviado",
             long,
             bottom,
             ~xOffset=25.,
             ~yOffset=50.,
           );
           navigation->Navigators.RootNavigator.Navigation.navigate("Social");
           resolve();
         })
      |> catch(_ => {
           open ReactNative.ToastAndroid;

           showWithGravityAndOffset(
             "Houve um erro no envio do E-Mail",
             long,
             bottom,
             ~xOffset=25.,
             ~yOffset=50.,
           );

           resolve();
         })
    )
    |> ignore;
  };

  ReactNative.(
    <View style={styles##bg}>
      <View style={styles##container}>
        <Text style={styles##orange}>
          {j|Conte-nos sua experiência:|j}->React.string
        </Text>
        <TextInput
          multiline=true
          numberOfLines=16
          style={styles##txtArea}
          onChangeText={text => setText(_ => text)}
        />
        <TouchableOpacity
          style={ReactNative.Style.style(~alignSelf=`flexEnd, ())}
          onPress=submit>
          <Text style={styles##txt}> "Enviar"->React.string </Text>
        </TouchableOpacity>
      </View>
      <View style={styles##bottom}>
        <Image
          style={styles##signature}
          source={Image.Source.fromRequired(
            Packager.require("../../images/signature.png"),
          )}
        />
        <Image
          style={styles##figure}
          source={Image.Source.fromRequired(
            Packager.require("../../images/30years.png"),
          )}
        />
      </View>
    </View>
  );
};