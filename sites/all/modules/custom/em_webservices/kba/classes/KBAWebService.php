<?php

include_once('transactiondirectiontype.php');
include_once('productcategorytype.php');
include_once('producttype.php');
include_once('persontype.php');
include_once('addresstype.php');
include_once('ukaddresstype.php');
include_once('phonenumbertype.php');
include_once('businesstype.php');
include_once('orderedbytype.php');
include_once('billtotype.php');
include_once('shiptotype.php');
include_once('sameastype.php');
include_once('paymentmethod.php');
include_once('purchasetype.php');
include_once('order.php');
include_once('modetype.php');
include_once('shippingmethod.php');
include_once('shippingtype.php');
include_once('settingstype.php');
include_once('dispositionsettingstype.php');
include_once('continuesettingstype.php');
include_once('resumesettingstype.php');
include_once('identityverificationsettingstype.php');
include_once('verificationtype.php');
include_once('venuetype.php');
include_once('pointofsale.php');
include_once('callcentertype.php');
include_once('onlinetype.php');
include_once('batchtype.php');
include_once('netviewtype.php');
include_once('birthdatetype.php');
include_once('addresscontexttype.php');
include_once('phonenumbercontexttype.php');
include_once('ssntype.php');
include_once('answertype.php');
include_once('answerselectiontype.php');
include_once('choicetype.php');
include_once('choicestype.php');
include_once('answerstype.php');
include_once('simulatormodetype.php');
include_once('tasktype.php');
include_once('transactionresulttype.php');
include_once('simpledetailtype.php');
include_once('complexdetailtype.php');
include_once('informationtype.php');
include_once('questiontype.php');
include_once('questionstype.php');
include_once('credentialmethodtype.php');
include_once('credentialtype.php');
include_once('transportlayertype.php');
include_once('pointofsaletype.php');
include_once('headerfieldstype.php');
include_once('httpheadertype.php');
include_once('headerfields.php');
include_once('browsertype.php');
include_once('languagevenuetype.php');
include_once('languagetype.php');
include_once('accountcategorytype.php');
include_once('accounttype.php');
include_once('accountactivitytype.php');
include_once('accountmaintenancecategorytype.php');
include_once('accountverificationtype.php');
include_once('securityquestioncategorytype.php');
include_once('securityquestiontype.php');
include_once('transactionstatustype.php');
include_once('transactiontype.php');
include_once('accountmaintenancetype.php');
include_once('accountoriginationtype.php');
include_once('customerservicetype.php');
include_once('informationcodetype.php');
include_once('attachmenttype.php');
include_once('threatassessment.php');
include_once('riskcategory.php');
include_once('riskcomponenttype.php');
include_once('riskassessmenttype.php');
include_once('fraudcategorytype.php');
include_once('dispositionstatustype.php');
include_once('dispositionresulttype.php');
include_once('assertiontype.php');
include_once('ivrtype.php');
include_once('specialfeaturetype.php');
include_once('internationalizationtype.php');
include_once('texttype.php');
include_once('identityassertiontype.php');
include_once('assertion.php');
include_once('assertionresponse.php');
include_once('transactionauthenticationcheck.php');
include_once('settings.php');
include_once('transactionresume.php');
include_once('transactionidentityverification.php');
include_once('transactioncontinue.php');
include_once('transactionresponse.php');
include_once('disposition.php');


/**
 * Knowledge based Authentication Web Service
 */
class KBAWebService extends SoapClient
{

  /**
   * 
   * @var array $classmap The defined classes
   * @access private
   */
  private static $classmap = array(
    'product-type' => 'producttype',
    'person-type' => 'persontype',
    'address-type' => 'addresstype',
    'uk-address-type' => 'ukaddresstype',
    'phone-number-type' => 'phonenumbertype',
    'business-type' => 'businesstype',
    'ordered-by-type' => 'orderedbytype',
    'bill-to-type' => 'billtotype',
    'ship-to-type' => 'shiptotype',
    'purchase-type' => 'purchasetype',
    'order' => 'order',
    'shipping-type' => 'shippingtype',
    'settings-type' => 'settingstype',
    'disposition-settings-type' => 'dispositionsettingstype',
    'continue-settings-type' => 'continuesettingstype',
    'resume-settings-type' => 'resumesettingstype',
    'identity-verification-settings-type' => 'identityverificationsettingstype',
    'verification-type' => 'verificationtype',
    'venue-type' => 'venuetype',
    'point-of-sale' => 'pointofsale',
    'callcenter-type' => 'callcentertype',
    'online-type' => 'onlinetype',
    'batch-type' => 'batchtype',
    'netview-type' => 'netviewtype',
    'birthdate-type' => 'birthdatetype',
    'answer-type' => 'answertype',
    'choice-type' => 'choicetype',
    'choices-type' => 'choicestype',
    'answers-type' => 'answerstype',
    'simple-detail-type' => 'simpledetailtype',
    'complex-detail-type' => 'complexdetailtype',
    'information-type' => 'informationtype',
    'question-type' => 'questiontype',
    'questions-type' => 'questionstype',
    'credential-type' => 'credentialtype',
    'transport-layer-type' => 'transportlayertype',
    'point-of-sale-type' => 'pointofsaletype',
    'header-fields-type' => 'headerfieldstype',
    'http-header-type' => 'httpheadertype',
    'header-fields' => 'headerfields',
    'browser-type' => 'browsertype',
    'account-type' => 'accounttype',
    'account-activity-type' => 'accountactivitytype',
    'account-verification-type' => 'accountverificationtype',
    'security-question-type' => 'securityquestiontype',
    'transaction-status-type' => 'transactionstatustype',
    'transaction-type' => 'transactiontype',
    'account-maintenance-type' => 'accountmaintenancetype',
    'account-origination-type' => 'accountoriginationtype',
    'customer-service-type' => 'customerservicetype',
    'risk-component-type' => 'riskcomponenttype',
    'risk-assessment-type' => 'riskassessmenttype',
    'assertion-type' => 'assertiontype',
    'ivr-type' => 'ivrtype',
    'special-feature-type' => 'specialfeaturetype',
    'internationalization-type' => 'internationalizationtype',
    'text-type' => 'texttype',
    'identity-assertion-type' => 'identityassertiontype',
    'assertion' => 'assertion',
    'assertion-response' => 'assertionresponse',
    'transaction-authentication-check' => 'transactionauthenticationcheck',
    'settings' => 'settings',
    'transaction-resume' => 'transactionresume',
    'transaction-identity-verification' => 'transactionidentityverification',
    'transaction-continue' => 'transactioncontinue',
    'transaction-response' => 'transactionresponse',
    'disposition' => 'disposition');

  /**
   * 
   * @param array $config A array of config values
   * @param string $wsdl The wsdl file to use
   * @access public
   */
  public function __construct(array $options = array(), $wsdl = 'input.wsdl')
  {
    foreach(self::$classmap as $key => $value)
    {
      if(!isset($options['classmap'][$key]))
      {
        $options['classmap'][$key] = $value;
      }
    }
    
    parent::__construct($wsdl, $options);
  }

  /**
   * 
   * @param transactionidentityverification $IdentityVerificationMsg
   * @access public
   */
  public function identityVerification($IdentityVerificationMsg)
  {
    
    $response = $this->__soapCall('identityVerification', array($IdentityVerificationMsg));
    $request  = $this->__getLastRequest();
    
    return array("response"=>$response, "request"=>$request);
  }

  /**
   * 
   * @param transactioncontinue $TransactionContinueMsg
   * @access public
   */
  public function continuation($TransactionContinueMsg)
  {
    return $this->__soapCall('continuation', array($TransactionContinueMsg));
  }

  /**
   * 
   * @param transactionresume $TransactionResumeMsg
   * @access public
   */
  public function resume($TransactionResumeMsg)
  {
    return $this->__soapCall('resume', array($TransactionResumeMsg));
  }

  /**
   * 
   * @param transactionauthenticationcheck $TransactionAuthenticationMsg
   * @access public
   */
  public function authenticationCheck($TransactionAuthenticationMsg)
  {
    return $this->__soapCall('authenticationCheck', array($TransactionAuthenticationMsg));
  }

  /**
   * 
   * @param assertion $AssertionMsg
   * @access public
   */
  public function assertion(assertion $AssertionMsg)
  {
    return $this->__soapCall('assertion', array($AssertionMsg));
  }

  /**
   * 
   * @param disposition $DispositionMsg
   * @access public
   */
  public function disposition(disposition $DispositionMsg)
  {
    return $this->__soapCall('disposition', array($DispositionMsg));
  }

}
