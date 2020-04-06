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
      "txtSmall": style(~fontSize=16., ()),
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
      "inputWrapper": style(~width=100.->pct, ()),
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
      "errorMessageText":
        style(
          ~fontSize=16.,
          ~fontFamily="Montserrat-SemiBold",
          ~color="rgb(254,80,0)",
          (),
        ),
      "horizontal": style(~flexDirection=`row, ()),
      "radio":
        style(
          ~backgroundColor="rgb(26,26,25)",
          ~height=40.->dp,
          ~width=40.->dp,
          ~alignItems=`center,
          ~marginTop=10.->dp,
          ~marginHorizontal=5.->dp,
          ~justifyContent=`flexEnd,
          ~borderRadius=100.,
          (),
        ),
      "radioActive": style(~backgroundColor="rgb(254,80,0)", ()),
      "txtRadio": style(~lineHeight=40., ()),
      "wrapper": style(~flex=4., ~justifyContent=`center, ()),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  open React;
  open Belt;
  open ReactNative;
  let emailRegexp = [%re "/[^@]+@[^\.]+\..+/"];

  let errorNoName = {j|Nome Obrigatório|j};
  let errorNoEmail = {j|E-Mail Obrigatório|j};
  let errorNoPhone = {j|Telefone Obrigatório|j};
  let errorEmailFormat = {j|Formato do email inválido|j};

  let (name, setName) = useState(() => "");

  let emailRef = useRef(Js.Nullable.null);
  let numberRef = useRef(Js.Nullable.null);

  let (email, setEmail) = useState(() => "");
  let (phone, setPhone) = useState(() => "");
  let (yesActive, setYesActive) = useState(() => false);
  let (errors, setErrors) = useState(() => Set.String.empty);

  React.useEffect2(
    () => {
      open Set.String;

      if (name === "") {
        setErrors(e => e->add(errorNoName));
      } else {
        setErrors(e => e->remove(errorNoName));
      };

      if (email === "") {
        setErrors(e => e->add(errorNoEmail));
      } else {
        setErrors(e => e->remove(errorNoEmail));
      };

      if (phone === "") {
        setErrors(e => e->add(errorNoPhone));
      } else {
        setErrors(e => e->remove(errorNoPhone));
      };

      Some(
        _ =>
          switch (email |> Js.String.match(emailRegexp)) {
          | Some(_email) => setErrors(e => e->remove(errorEmailFormat))
          | None => setErrors(e => e->add(errorEmailFormat))
          },
      );
    },
    (name, email),
  );

  let submit = _ => {
    navigation->RootNavigator.Navigation.navigate("Options");
    Keyboard.dismiss();
    // let text = {j|Olá! Meu nome é $name e meu email é $email. Gostaria de falar com uma atendente.|j};
    // let url = {j|whatsapp://send?text=$text&phone=5583999651707|j};
    // errors->Set.String.isEmpty
    //   ? Js.Promise.(
    //       Linking.canOpenURL(url)
    //       |> then_(can =>
    //            can
    //              ? Linking.openURL(url) |> then_(() => resolve(true))
    //              : reject(raise(Not_found))
    //          )
    //       |> catch(_ => {
    //            resolve(false);
    //          })
    //     )
    //     |> ignore
    //   : ();
  };

  <View style={styles##bg}>
    <View style={styles##container}>
      <View style={styles##wrapper}>
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
              numberRef
              ->React.Ref.current
              ->Js.Nullable.toOption
              ->Option.map(number => number->TextInput.focus)
              ->ignore
            }}
          />
          {errors->Set.String.has(errorNoName)
             ? <View>
                 <Text style={styles##errorMessageText}>
                   errorNoName->React.string
                 </Text>
               </View>
             : React.null}
        </View>
        <View style={styles##inputWrapper}>
          <Text style={styles##txt}> "Telefone"->React.string </Text>
          <TextInput
            returnKeyType=`next
            style={styles##input}
            blurOnSubmit=false
            ref=numberRef
            keyboardType=`phonePad
            onChangeText={e => setPhone(_ => e)}
            onSubmitEditing={_ => {
              emailRef
              ->React.Ref.current
              ->Js.Nullable.toOption
              ->Option.map(email => email->TextInput.focus)
              ->ignore
            }}
          />
          <View style={styles##horizontal}>
            <Text style={Style.array([|styles##txt, styles##txtSmall|])}>
              {j|Aplicativo de Mensagem?|j}->React.string
            </Text>
            <View
              style={Style.listOption([
                Some(styles##radio),
                yesActive ? Some(styles##radioActive) : None,
              ])}>
              <TouchableNativeFeedback
                background={TouchableNativeFeedback.Background.ripple(
                  "#fff",
                  true,
                )}
                onPress={_ => setYesActive(_ => true)}>
                <Text
                  style={Style.list([
                    styles##txt,
                    styles##txtSmall,
                    styles##txtRadio,
                  ])}>
                  {j|Sim|j}->React.string
                </Text>
              </TouchableNativeFeedback>
            </View>
            <View
              style={Style.listOption([
                Some(styles##radio),
                yesActive ? None : Some(styles##radioActive),
              ])}>
              <TouchableNativeFeedback
                background={TouchableNativeFeedback.Background.ripple(
                  "#fff",
                  true,
                )}
                onPress={_ => setYesActive(_ => false)}>
                <Text
                  style={Style.list([
                    styles##txt,
                    styles##txtSmall,
                    styles##txtRadio,
                  ])}>
                  {j|Não|j}->React.string
                </Text>
              </TouchableNativeFeedback>
            </View>
          </View>
          {errors->Set.String.has(errorNoPhone)
             ? <View>
                 <Text style={styles##errorMessageText}>
                   {errors->Set.String.has(errorNoPhone)
                      ? errorNoPhone->React.string : React.null}
                 </Text>
               </View>
             : React.null}
        </View>
        <View style={styles##inputWrapper}>
          <Text style={styles##txt}> "E-Mail"->React.string </Text>
          <TextInput
            returnKeyType=`go
            style={styles##input}
            ref=emailRef
            keyboardType=`emailAddress
            onChangeText={e => setEmail(_ => e)}
            onSubmitEditing=submit
          />
          {errors->Set.String.has(errorNoEmail)
           || errors->Set.String.has(errorEmailFormat)
             ? <View>
                 <Text style={styles##errorMessageText}>
                   {errors->Set.String.has(errorNoEmail)
                      ? errorNoEmail->React.string : React.null}
                 </Text>
                 <Text style={styles##errorMessageText}>
                   {errors->Set.String.has(errorEmailFormat)
                      ? errorEmailFormat->React.string : React.null}
                 </Text>
               </View>
             : React.null}
        </View>
      </View>
      <SubmitButton errors submit />
    </View>
  </View>;
};