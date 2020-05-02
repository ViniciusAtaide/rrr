module Form = [%form
  {target: ReactNative};
  type input = {
    text: string,
    name: string,
    number: string,
  };
  let validators = {
    name: {
      strategy: OnFirstChange,
      validate: input =>
        switch (input.name) {
        | "" => Error({j|Nome Obrigatório.|j})
        | _ => Ok(input.name)
        },
    },
    number: {
      strategy: OnFirstChange,
      validate: input =>
        switch (input.number) {
        | "" => Error({j|Telefone Obrigatório.|j})
        | _ => Ok(input.number)
        },
    },
    text: {
      strategy: OnFirstChange,
      validate: input =>
        switch (input.text) {
        | "" => Error({j|Texto Obrigatório.|j})
        | _ => Ok(input.text)
        },
    },
  }
];

let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container":
        style(~justifyContent=`flexEnd, ~paddingHorizontal=25.->dp, ()),
      "middle":
        style(
          ~justifyContent=`center,
          ~alignItems=`flexStart,
          ~width=100.->pct,
          ~height=800.->dp,
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
      "txtInput":
        style(
          ~fontFamily="Montserrat-Regular",
          ~backgroundColor="white",
          ~fontSize=22.,
          ~marginVertical=10.->dp,
          ~padding=10.->dp,
          ~width=100.->pct,
          (),
        ),

      "txtArea":
        style(
          ~backgroundColor="white",
          ~fontFamily="Montserrat-Regular",
          ~marginTop=10.->dp,
          ~minHeight=280.->dp,
          ~width=100.->pct,
          (),
        ),
      "errorMessageText":
        style(
          ~fontSize=16.,
          ~fontFamily="Montserrat-SemiBold",
          ~color="rgb(254,80,0)",
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~fontFamily="Montserrat-Bold",
          ~fontSize=20.,
          (),
        ),
      "signature":
        style(~width=150.->dp, ~height=90.->dp, ~alignSelf=`center, ()),
      "figure":
        style(~width=150.->dp, ~height=50.->dp, ~alignSelf=`center, ()),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  let numberRef = React.useRef(Js.Nullable.null);
  let textRef = React.useRef(Js.Nullable.null);

  let form =
    Form.useForm(
      ~initialInput={text: "", name: "", number: ""},
      ~onSubmit=(output, cb) => {
        let {name, number, text}: Form.output = output;

        let url = "https://api.mailgun.net/v3/mia.adv.br/messages";

        let p =
          Js.Dict.fromList([
            ("from", Js.Json.string("mailgun <mailgun@mia.adv.br>")),
            ("to", Js.Json.string("marketing@marcosinacio.com.br")),
            ("subject", Js.Json.string("Contato")),
            (
              "html",
              Js.Json.string(
                {j|<h1>Nome: $name</h1>, <h2>Fone: $number</h2> <p>$text</p>|j},
              ),
            ),
          ]);

        let d = Qs.stringify(p);

        Js.Promise.(
          Fetch.fetchWithInit(
            url,
            Fetch.RequestInit.make(
              ~headers=
                Fetch.HeadersInit.makeWithArray([|
                  ("Content-Type", "application/x-www-form-urlencoded"),
                  (
                    "Authorization",
                    "Bearer YXBpOjA0MTA4M2U0MmFiNWY3N2ZkMzEyN2I0NzE4MzZlNzI4LTQ2YWM2YjAwLTk5NzM0OWNj",
                  ),
                |]),
              ~body=Fetch.BodyInit.make(d),
              ~method_=Post,
              (),
            ),
          )
          |> then_(Fetch.Response.json)
          |> then_(res => {
               open ReactNative.ToastAndroid;
               showWithGravityAndOffset(
                 "Email Enviado",
                 long,
                 bottom,
                 ~xOffset=0.,
                 ~yOffset=50.,
               );
               ReactNative.Keyboard.dismiss();
               cb.reset();

               navigation->Navigators.RootNavigator.Navigation.navigate(
                 "Media",
               );

               resolve(res);
             })
        )
        |> ignore;
      },
    );

  ReactNative.(
    <TouchableWithoutFeedback onPress={_ => Keyboard.dismiss()}>
      <ScrollView style={styles##bg}>
        <View style={styles##container}>
          <View style={styles##middle}>
            <Text style={styles##orange}>
              {j|Conte-nos sua experiência:|j}->React.string
            </Text>
            <TextInput
              style={styles##txtInput}
              placeholder="Nome"
              returnKeyType=`next
              blurOnSubmit=false
              onChangeText={name =>
                form.updateName(input => {...input, name})
              }
              onSubmitEditing={_ => {
                numberRef
                ->React.Ref.current
                ->Js.Nullable.toOption
                ->Belt.Option.map(number => number->TextInput.focus)
                ->ignore
              }}
            />
            {switch (form.nameResult) {
             | Some(Error(message)) =>
               <View>
                 <Text style={styles##errorMessageText}>
                   message->React.string
                 </Text>
               </View>
             | Some(Ok(_))
             | None => React.null
             }}
            <TextInput
              placeholder={j|Telefone (com DDD)|j}
              returnKeyType=`next
              blurOnSubmit=false
              style={styles##txtInput}
              ref=numberRef
              onSubmitEditing={_ => {
                textRef
                ->React.Ref.current
                ->Js.Nullable.toOption
                ->Belt.Option.map(text => text->TextInput.focus)
                ->ignore
              }}
              onChangeText={number =>
                form.updateNumber(input => {...input, number})
              }
              keyboardType=`phonePad
            />
            {switch (form.numberResult) {
             | Some(Error(message)) =>
               <View>
                 <Text style={styles##errorMessageText}>
                   message->React.string
                 </Text>
               </View>
             | Some(Ok(_))
             | None => React.null
             }}
            <TextInput
              multiline=true
              numberOfLines=16
              ref=textRef
              style={styles##txtArea}
              onChangeText={text =>
                form.updateText(input => {...input, text})
              }
            />
            {switch (form.textResult) {
             | Some(Error(message)) =>
               <View>
                 <Text style={styles##errorMessageText}>
                   message->React.string
                 </Text>
               </View>
             | Some(Ok(_))
             | None => React.null
             }}
            <TouchableOpacity
              style={ReactNative.Style.style(~alignSelf=`flexEnd, ())}
              onPress={_ => form.submit()}>
              <Text style={styles##txt}>
                {form.submitting
                   ? "Carregando"->React.string : "Enviar"->React.string}
              </Text>
            </TouchableOpacity>
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
      </ScrollView>
    </TouchableWithoutFeedback>
  );
};