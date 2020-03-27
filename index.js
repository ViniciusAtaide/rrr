/**
 * @format
 */

import {AppRegistry} from 'react-native';
import App from './App';
import {YellowBox} from 'react-native';

const APP_NAME = 'rr';

AppRegistry.registerComponent(APP_NAME, () => App);
YellowBox.ignoreWarnings(['Warning: ...']);
