let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~flex=1., ()),
      "container":
        style(
          ~height=100.->pct,
          ~width=100.->pct,
          ~alignContent=`spaceAround,
          ~padding=25.->dp,
          ~flex=1.,
          (),
        ),
      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="#fff",
          ~fontSize=22.,
          ~paddingTop=20.->dp,
          (),
        ),
      "txtBlk":
        style(
          ~fontFamily="Montserrat-Bold",
          ~color="black",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
      "txtGray":
        style(
          ~fontFamily="Montserrat-Light",
          ~color="gray",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
      "inputWrapper": style(~marginVertical=2.5->dp, ~width=100.->pct, ()),
      "input": style(~backgroundColor="#fff", ~height=40.->dp, ()),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~fontFamily="Montserrat-Bold",
          ~fontSize=22.,
          (),
        ),

      "button":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~backgroundColor="#fff",
          ~fontSize=28.,
          ~width=100.->pct,
          ~alignItems=`center,
          (),
        ),
      "buttonWrapper": style(~flex=1., ~justifyContent=`flexEnd, ()),
      "errorMessage": style(~opacity=0., ()),
      "errorMessageText":
        style(
          ~fontSize=16.,
          ~fontFamily="Montserrat-SemiBold",
          ~color="rgb(254,80,0)",
          (),
        ),
      "errorMessageActive": style(~opacity=1., ()),
      "wrapper": style(~flex=1.3, ~justifyContent=`flexEnd, ()),
    })
  );

[@react.component]
let make = (~navigation as _, ~route as _) => {
  open React;
  open Belt;
  open ReactNative;
  let emailRegexp = [%re "/[^@]+@[^\.]+\..+/"];

  let errorNoName = {j|Nome Obrigatório|j};
  let errorNoEmail = {j|E-Mail Obrigatório|j};
  let errorEmailFormat = {j|Formato do email inválido|j};

  let (name, setName) = useState(() => "");

  let emailRef = useRef(Js.Nullable.null);

  let (email, setEmail) = useState(() => "");
  let (errors, setErrors) = useState(() => Set.String.empty);
  let (errorNoWhats, setErrorNoWhats) = useState(() => false);

  React.useEffect2(
    () => {
      if (name === "") {
        setErrors(e => e->Set.String.add(errorNoName));
      } else {
        setErrors(e => e->Set.String.remove(errorNoName));
      };

      if (email === "") {
        setErrors(e => e->Set.String.add(errorNoEmail));
      } else {
        setErrors(e => e->Set.String.remove(errorNoEmail));
      };

      Js.log(errors->Set.String.isEmpty);

      Some(
        _ =>
          switch (email |> Js.String.match(emailRegexp)) {
          | Some(_email) =>
            setErrors(e => e->Set.String.remove(errorEmailFormat))
          | None => setErrors(e => e->Set.String.add(errorEmailFormat))
          },
      );
    },
    (name, email),
  );

  let submit = _ => {
    let text = {j|Olá! Meu nome é $name e meu email é $email. Gostaria de falar com uma atendente.|j};
    let url = {j|whatsapp://send?text=$text&phone=5583999651707|j};

    errors->Set.String.isEmpty
      ? Js.Promise.(
          Linking.canOpenURL(url)
          |> then_(can =>
               can
                 ? Linking.openURL(url) |> then_(() => resolve(true))
                 : reject(raise(Not_found))
             )
          |> catch(_ => {
               setErrorNoWhats(_ => true);
               resolve(false);
             })
        )
        |> ignore
      : ();
  };

  <View style={styles##bg}>
    <KeyboardAvoidingView behavior=`height style={styles##container}>
      <SafeAreaView style={styles##wrapper}>
        <Text style={styles##orange}>
          {j|Vamos conversar?!|j}->React.string
        </Text>
        <View style={styles##inputWrapper}>
          <Text style={styles##txt}> "Qual seu nome?"->React.string </Text>
          <TextInput
            returnKeyType=`next
            blurOnSubmit=false
            style={styles##input}
            onChangeText={name => setName(_ => name)}
            onSubmitEditing={_ => {
              emailRef
              ->React.Ref.current
              ->Js.Nullable.toOption
              ->Option.map(email => email->TextInput.focus)
              ->ignore
            }}
          />
          <View
            style={Style.arrayOption([|
              Some(styles##errorMessage),
              errors->Set.String.has(errorNoName)
                ? Some(styles##errorMessageActive) : None,
            |])}>
            <Text style={styles##errorMessageText}>
              errorNoName->React.string
            </Text>
          </View>
        </View>
        <View style={styles##inputWrapper}>
          <Text style={styles##txt}> "Informe seu E-Mail"->React.string </Text>
          <TextInput
            returnKeyType=`go
            style={styles##input}
            ref=emailRef
            onChangeText={e => setEmail(_ => e)}
            onSubmitEditing=submit
          />
          <View
            style={Style.arrayOption([|
              Some(styles##errorMessage),
              errors->Set.String.has(errorNoEmail)
              || errors->Set.String.has(errorEmailFormat)
                ? Some(styles##errorMessageActive) : None,
            |])}>
            <Text style={styles##errorMessageText}>
              {errors->Set.String.has(errorNoEmail)
                 ? errorNoEmail->React.string : React.null}
            </Text>
            <Text style={styles##errorMessageText}>
              {errors->Set.String.has(errorEmailFormat)
                 ? errorEmailFormat->React.string : React.null}
            </Text>
          </View>
        </View>
      </SafeAreaView>
      <View style={styles##buttonWrapper}>
        <View style={styles##button}>
          <TouchableNativeFeedback
            background={TouchableNativeFeedback.Background.ripple(
              "#000",
              false,
            )}
            onPress=submit>
            <Text
              style={Style.arrayOption([|
                !errors->Set.String.isEmpty
                  ? Some(styles##txtGray) : Some(styles##txtBlk),
                errorNoWhats ? Some(styles##orange) : None,
              |])}>
              {!errorNoWhats
                 ? "CONTINUAR"->React.string
                 : "INSTALE O WHATSAPP"->React.string}
            </Text>
          </TouchableNativeFeedback>
        </View>
      </View>
    </KeyboardAvoidingView>
  </View>;
};