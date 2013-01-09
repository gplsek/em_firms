<?php

require_once "classes/KBAWebService.php";

/**
 * Settings
 */
variable_set("rsa_username", "EmergingFirmsINTEG");
variable_set("rsa_password", '$u85ApDR!c2');
variable_set("rsa_ruleset", "customers.emergingfirms.compapp.4quest");
variable_set("rsa_account", "Customers:EmergingFirms:CompanyApp");
variable_set("rsa_state", "simulated"); // pilot, testing, simulated
variable_set("rsa_api_trace", 1); // used for debugging

/**
 * KBA error codes
 */
define("KBA_ERROR_SERVICE_CANNOT_BE_REACHED", 1);
define("KBA_ERROR_PERSONAL_INFORMATION", 2);
define("KBA_ERROR_TWO_OR_MORE_QUESTIONS_WRONG", 3);
define("KBA_ERROR_FOLLOW_UP_QUESTION_WRONG", 4);

/**
 * Associative array of the form steps
 *
 * @return array form wizard steps
 */
function _kba_steps() {
  return array(
	  1 => array(
        'form' => 'kba_personal_info',
      ),
      2 => array(
        'form' => 'kba_questions',
      ),
      3 => array(
        'form' => 'kba_follow_up_question',
      ),
      4 => array(
        'form' => 'kba_follow_up_question_result',
      )
    );
}

/**
 * Entry point to the KBA wizard
 *
 * @return array a form in the Drupal Form API format
 */
function kba_wizard($form, &$form_state, $nid) {
  context_set('eiq_commerce', 'partner', 'kiva-zip');
  $form_state['node'] = $nid;
  // Initialize a description of the steps for the wizard.
  if (empty($form_state['step'])) {
    $form_state['step'] = 1;

    // This array contains the function to be called at each step to get the
    // relevant form elements. It will also store state information for each
    // step.
    $form_state['step_information'] = _kba_steps();
  }

  $step = &$form_state['step'];
  drupal_set_title(t('Verification: Step @step', array('@step' => $step)));

  // Call the function named in $form_state['step_information'] to get the
  // form elements to display for this step.
  $form = $form_state['step_information'][$step]['form']($form, $form_state);


  // Show the Next button only if there are more steps defined.
  if ($step < count($form_state['step_information'])) {
    // The Next button should be included on every step
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#name' => 'next',
      '#submit' => array('kba_wizard_next_submit'),
    );
  }
  else {
    // Just in case there are no more steps, we use the default submit handler
    // of the form wizard. Call this button Finish, Submit, or whatever you
    // want to show. When this button is clicked, the
    // kba_wizard_submit handler will be called.
    $form['finish'] = array(
      '#type' => 'submit',
      '#value' => t('Finish'),
    );
  }

  // Include each validation function defined for the different steps.
  if (function_exists($form_state['step_information'][$step]['form'] . '_validate')) {
    $form['next']['#validate'] = array($form_state['step_information'][$step]['form'] . '_validate');
  }


  return $form;
}

/**
 * Submit handler for the "previous" button.
 * - Stores away $form_state['values']
 * - Decrements the step counter
 * - Replaces $form_state['values'] with the values from the previous state.
 * - Forces form rebuild.
 *
 * @return array a form in the Drupal Form API format
 */
function kba_wizard_previous_submit($form, &$form_state) {
	context_set('eiq_commerce', 'partner', 'kiva-zip');
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
  if ($current_step > 1) {
    $current_step--;
    $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the 'next' button.
 * - Saves away $form_state['values']
 * - Increments the step count.
 * - Replace $form_state['values'] from the last time we were at this page
 *   or with array() if we haven't been here before.
 * - Force form rebuild.
 *
 * @param $form
 * @param $form_state
 *
 * @return array a form in the Drupal Form API format
 */
function kba_wizard_next_submit($form, &$form_state) {

	context_set('eiq_commerce', 'partner', 'kiva-zip');
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
  if ($current_step < count($form_state['step_information'])) {
    $current_step++;
    if (!empty($form_state['step_information'][$current_step]['stored_values'])) {
      $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
    }
    else {
      $form_state['values'] = array();
    }


    $form_state['rebuild'] = TRUE;  // Force rebuild with next step.
    return;
  }
}

/**
 * Retrieves the personal information form, to be sent to get the KBA questions
 *
 * @return array a form in the Drupal Form API format
 */
function kba_personal_info($form, &$form_state) {
	context_set('eiq_commerce', 'partner', 'kiva-zip');
    global $user;



    $node = node_load($form_state['node']);
    if($node->field_verify_count['und'][0]['value'] >= 2){
           	  drupal_set_message("You have exceeded the maximum amount of verification attempts","status");
           	  drupal_goto('verification/'.$form_state['node'].'/status');
               }
    $address = entity_load('field_collection_item', array($node->field_address['und'][0]['value']));

    if($node->uid <> $user->uid){
      return "You are not authorized";
    }
    $form['message'] = array(
    	'#markup' => t('<h3>The following page is the final step in your application. You will be presented with questions to verify your identity. You will have 3 minutes to answer the multiple-choice questions. Click Next to begin</h3>'),
    );
    $form['data'] = array(
    	'#type' => 'fieldset',
        '#access' => FALSE
    );
    $form['data']['data_person_nid'] = array(
        '#type' => 'hidden',
        '#default_value' => $form_state['node'],

    );
    $form['data']['suffix'] = array(
        '#title' => t('Suffix'),
        '#type' => 'textfield',
        '#default_value' => $node->field_name_suffix['und'][0]['value'],

    );
    $form['data']['first_name'] = array(
        '#title' => t('First Name'),
        '#type' => 'textfield',
        '#default_value' => !empty($form_state['values']['first_name']) ? $form_state['values']['first_name'] : $node->field_name_first['und'][0]['value']

    );
    $form['data']['middle_name'] = array(
        '#title' => t('Middle Name'),
        '#type' => 'textfield',
        '#default_value' => !empty($form_state['values']['middle_name']) ? $form_state['values']['middle_name'] : $node->field_name_middle['und'][0]['value']
    );
    $form['data']['last_name'] = array(
        '#title' => t('Last Name'),
        '#type' => 'textfield',
        '#default_value' => !empty($form_state['values']['last_name']) ? $form_state['values']['last_name'] : $node->field_name_last['und'][0]['value']

    );
    $form['data']['maiden_name'] = array(
        '#title' => t('Maiden Name'),
        '#type' => 'textfield',
        '#default_value' => $node->field_name_maiden['und'][0]['value'],

    );
    $dob = $node->field_dob['und'][0]['value'];
    $dob = str_replace(' 00:00:00','',$dob);
    $dob = explode('-',$dob);

    $form['data']['birthdate'] = array(
      '#title' => t('Birthdate'),
      '#type' => 'date',
      '#description' => t('Select your birthdate'),
      '#default_value' => array(
            'month' => str_replace('0','',$dob[1]),
            'day' => str_replace('0','',$dob[2]),
            'year' => $dob[0],
         )
    );
    $form['data']['gender'] = array(
      '#title' => t('Gender'),
      '#type' => 'select',
      '#description' => t('Select your gender'),
      '#options' => array('Male' => 'Male', 'Female' => 'Female'),
      '#default_value' => !empty($form_state['values']['gender']) ? $form_state['values']['gender'] : $node->field_gender['und'][0]['value']
    );

    $form['data']['ssn'] = array(
        '#title' => t('Social Security Number'),
        '#type' => 'textfield',
        '#default_value' => !empty($form_state['values']['ssn']) ? $form_state['values']['ssn'] : aes_decrypt($_SESSION['piissn'])
    );

    $form['data']['address'] = array(
    '#type' => 'addressfield',
    '#title' => t('Address'),
    '#required' => TRUE,
    //'#default_value' => array('country' => 'US'), // Selects USA by default
    '#default_value' => $address[$node->field_address['und'][0]['value']]->field_address_full['und'][0],
    '#description' => "Please enter your address."
  );

    return $form;
}

/**
 * Retrieves the KBA questions
 *
 * @return array a form in the Drupal Form API format
 */
function kba_questions($form, &$form_state) {
	context_set('eiq_commerce', 'partner', 'kiva-zip');
    global $user;

   $node = node_load($form_state['node']);
   if($node->uid <> $user->uid){
      return "You are not authorized";
   }
   // check if user has compled more than 2 times

   if($node->field_verify_count['und'][0]['value'] >= 2){
        	  drupal_set_message("You have exceeded the maximum amount of verification attempts","status");
        	  drupal_goto('verification/'.$form_state['node'].'/status');
        }


 if(!empty($form_state["step_information"]) && !empty($form_state["step_information"][1])) {

    //$personalInformation = $form_state["step_information"][1];

    try {
      //$response = json_decode(_ws_verification($personalInformation["stored_values"]), true);
      $response = json_decode(_ws_verification($form_state['node']), true);

      $transationID = $response["transaction-status"]["transaction-id"];

      $form['transaction_id'] = array(
            '#type' => 'hidden',
            '#default_value' => $transationID,

        );

      $questions = $response["questions"]["question"];

      if(!empty($questions)) {

        $questionSetID = $response["questions"]["question-set-id"];

        $form['message'] = array(
	    	'#markup' => '<h2>This page is the final step in your application. You will be presented with questions to verify your identity. You will have 3 minutes to answer the multiple-choice questions.</h2>',
	    );

        $form['question_set_id'] = array(
            '#type' => 'hidden',
            '#default_value' => $questionSetID,
        );

        foreach($questions as $question) {

          $questionTitle = $question["text"]["statement"];
          $questionID = $question["question-id"];
          $helpText = $question["help-text"]["statement"];

          $questionOptions = $question["choice"];

          // Form API question options
          $questionFormOptions = array();
          foreach($questionOptions as $questionOption) {
             $questionFormOptions[$questionOption["choice-id"]] = $questionOption["text"]["statement"];
          }

          $form["Question_".$questionID] = array(
            '#type'=>'radios',
            '#required' => TRUE,
            '#options'=>$questionFormOptions,
            '#title'=>t($questionTitle),
            '#description'=>t($helpText)
          );
        }

      } else {

        kba_failed($form_state, KBA_ERROR_PERSONAL_INFORMATION);



      }

    } catch (Exception $e) {

        kba_failed($form_state, KBA_ERROR_SERVICE_CANNOT_BE_REACHED);


    }
  }

  return $form;
}

/**
 * Retrieves the follow up question or a you have passed message.
 *
 * @return array a form in the Drupal Form API format
 */
function kba_follow_up_question($form, &$form_state) {
  context_set('eiq_commerce', 'partner', 'kiva-zip');
  $form = array();

  if(!empty($form_state["step_information"]) && !empty($form_state["step_information"][2])) {
    $answers = $form_state["step_information"][2];
    $response = json_decode(_ws_question_answers($answers["stored_values"]), true);

    $question = $response["questions"]["question"];

    // User missed a question, ask the follow up question
    if(!empty($question)) {
      $transationID = $response["transaction-status"]["transaction-id"];

      $form['transaction_id'] = array(
            '#type' => 'hidden',
            '#default_value' => $transationID,

        );

      $questionSetID = $response["questions"]["question-set-id"];

      $form['question_set_id'] = array(
            '#type' => 'hidden',
            '#default_value' => $questionSetID,
        );

      $questionTitle = $question["text"]["statement"];
      $questionID = $question["question-id"];
      $helpText = $question["help-text"]["statement"];

      $questionOptions = $question["choice"];

      // Form API question options
      $questionFormOptions = array();
      foreach($questionOptions as $questionOption) {
         $questionFormOptions[$questionOption["choice-id"]] = $questionOption["text"]["statement"];
      }

      $form["Question_".$questionID] = array(
        '#type'=>'radios',
        '#required' => TRUE,
        '#options'=>$questionFormOptions,
        '#title'=>t($questionTitle),
        '#description'=>t($helpText)
      );

    } else {

      if(!empty($response["information"]["detail-code"]) && $response["information"]["detail-code"] == "passed") {
        //User has passed
        kba_passed($form_state);
      } else {
        // User has failed
        kba_failed($form_state, KBA_ERROR_TWO_OR_MORE_QUESTIONS_WRONG);
      }

       drupal_goto('node/'.$form_state['node'].'/edit');


      $form_state["steps"] = 9999;

    }


  }
  return $form;
}

/**
 * Retrieves the result of the KBA
 *
 * @return array a form in the Drupal Form API format
 */
function kba_follow_up_question_result($form, &$form_state) {
	context_set('eiq_commerce', 'partner', 'kiva-zip');
  $form = array();

  if(!empty($form_state["step_information"]) && !empty($form_state["step_information"][3])) {
    $answers = $form_state["step_information"][3];
    $response = json_decode(_ws_question_answers($answers["stored_values"]), true);

    if(!empty($response["information"]["detail-code"]) && $response["information"]["detail-code"] == "passed") {

      //User has passed
      kba_passed($form_state);


    } else {

      // User has failed
      kba_failed($form_state, KBA_ERROR_FOLLOW_UP_QUESTION_WRONG);

    }



  }

  return $form;
}





/**
 * Wizard form submit handler.
 * - Saves away $form_state['values']
 * - Process all the form values.
 *
 * This demonstration handler just do a drupal_set_message() with the information
 * collected on each different step of the wizard.
 *
 * @param $form
 * @param $form_state
 *
 * @ingroup kb
 */
function kba_wizard_submit($form, &$form_state) {

  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];

  // In this case we've completed the final page of the wizard, so process the
  // submitted information.
  foreach ($form_state['step_information'] as $index => $value) {
    // Remove FAPI fields included in the values (form_token, form_id and form_build_id
    // This is not required, you may access the values using $value['stored_values']
    // but I'm removing them to make a more clear representation of the collected
    // information as the complete array will be passed through drupal_set_message().
    unset($value['stored_values']['form_id']);
    unset($value['stored_values']['form_build_id']);
    unset($value['stored_values']['form_token']);

  }
}

/**
 * Sends the personal information to the KBA in order to retreive questions
 *
 * @return string the json of the response, or null if empty.
 */
function _ws_verification($nid) {

  $webService = _createWebService();

  $ssn = aes_decrypt($_SESSION['piissn']);
  $node = node_load($nid);
  $address = entity_load('field_collection_item', array($node->field_address['und'][0]['value']));
  $dob = $node->field_dob['und'][0]['value'];
  $dob = str_replace(' 00:00:00','',$dob);
  $dob = explode('-',$dob);

  $personID   = $nid;
  $firstName  = $node->field_name_first['und'][0]['value'];
  $lastName   = $node->field_name_last['und'][0]['value'];
  $ssn        = preg_replace('/[^0-9]/', '', $ssn); // removes any non-integer characters
  $birthYear  = $dob[0];
  $birthMonth = $dob[1];
  $birthDay   = $dob[2];
  $addy = $address[$node->field_address['und'][0]['value']]->field_address_full['und'][0];

  $address1   = $addy["thoroughfare"];
  $address2   = $addy["premise"];
  $addressCity  = $addy["locality"];
  $addressState = $addy["administrative_area"];
  $addressZip   = $addy["postal_code"];

  $settings = _getWebServiceSettings();
  $settings["task"] = "iauth"; // adding an additional setting for this specific call


  $requestData = array(
      "settings" => $settings,
      "person" => array(
          "name-first" => $firstName,
          "name-last"  => $lastName,
          "ssn" => $ssn,
          "ssn-type" => "ssn9",
          "birthdate" => array(
              "year" => $birthYear,
              "month" => $birthMonth,
              "day" => $birthDay
          ),
          "address" => array(
              "address-street1" => $address1,
              "address-street2" => $address2,
              "address-city"    => $addressCity,
              "address-state"   => $addressState,
              "address-zip"     => $addressZip,
              "address-context" => "primary"
          )
      ),
      "transaction" => array(
          "account-verification" => array(
              "account-maintenance" => array(
                  "account" => array(
                      "customer-id" => $personID
                  )
              ),
              "venue" => array(
                  "online" => array(
                      "credential" => array(
                                "credential-method" => "ssn"
                      )
                  )
              ),
              "activity-date" => gmdate("c") // current datetime in GMT and in the ISO 8601 format.
          )
      )
  );

  $data = $webService->identityVerification($requestData);

  // ----------------------------- FOR TESTING PURPOSES ------------------------------

  //      echo "<h1>------REQUEST-----</h1><br>";
  //      echo '<pre>' . xmlpp($data["request"], true) . '</pre>';
  //      echo "<br/><br/><h1>------RESPONSE-----</h1><br>";
  //      echo json_pretty(json_encode($data["response"]), array("format"=>"html"));
   // --------------------------------------------------------------------------------



  $results = null;
  if(!empty($data) && !empty($data["response"])) {
    $results = json_encode($data["response"]);
  }

  return $results;
}

/**
 * Sends the answers to the KBA, retrieves the response in JSON
 *
 * @return string the json of the response, or null if empty.
 */
function _ws_question_answers($data) {

  $webService = _createWebService();

  $transactionID = $data["transaction_id"];
  $questionSetID = $data["question_set_id"];
  $answers = array();

  foreach($data as $key => $value) {

    $key = strtolower($key); // lowercase fieldname

    // get the integer from the fieldname
    $questionID = intval(substr($key, 9));

    if(!empty($questionID) && is_integer($questionID)) {
      $answers[] = array(
        "question-id" => $questionID,
        "choices" => array(
          "choice-id" => $value
        )
      );
    }

  }

  $settings = _getWebServiceSettings();
  $settings["transaction-id"] = $transactionID; // adding an additional setting for this specific call

  $requestData = array(
      "settings" => $settings,
      "answers" => array(
          "question-set-id" => $questionSetID,
          "answer"  => $answers
      )
  );

  $data = $webService->continuation($requestData);

  // TESTING
  //    echo "<br/><br/><h1>------RESPONSE-----</h1><br>";
  //    echo json_pretty(json_encode($data), array("format"=>"html"));


  $results = null;
  if(!empty($data)) {
    $results = json_encode($data);
  }

  return $results;
}

/**
 * Creates the KBA webservice with the default settings
 *
 * @return KBAWebService the KBA class
 */
function _createWebService() {

  return new KBAWebService(
    array(
      "login" => variable_get("rsa_username"),
      "password" => variable_get("rsa_password"),
      'trace' => variable_get("rsa_api_trace")
    ),
    dirname(__FILE__)."/rsa_kba.wsdl" // real path to the RSA KBA wsdl
  );
}

/**
 * Retrieves the RSA KBA web service settings
 *
 * @return array the default settings for the RSA KBA API
 */
function _getWebServiceSettings() {
  return array(
    "account-name" => variable_get("rsa_account"),
    "mode" => variable_get("rsa_state"),
    "ruleset" => variable_get("rsa_ruleset"),

    // Settings for simulated mode
    //"mode" => "simulated",
    "simulator-mode"=>"questions"

  );
}

/**
 * Called when the user has passed the KBA process
 *
 * @param array The form state when the user passed
 */
function kba_passed($form_state) {
	//TO DO:  update the KBA complete flag and change node ownership
	$node = node_load($form_state['node']);
	$cnid = $node->field_company['und'][0]['nid'];
	$company = node_load($cnid);
	$node->uid = $company->uid;
	$node->field_kba['und'][0]['value'] = 1;
	$node->field_verify_count['und'][0]['value'] = $node->field_verify_count['und'][0]['value'] + 1;
	node_save($node);
   _eiq_partners_notify_analyst($form_state['node'],$company->uid, 'pass');
   drupal_goto('verification/'.$form_state['node'].'/complete');

}

function em_webservices_complete($nid){
   context_set('eiq_commerce', 'partner', 'kiva-zip');
	//show thanks for playin page KIVA values only now
	$rows = array();
	$header = array();
	$message = "Success! You're done with the application
	process.";
	drupal_set_message($message,'status');

	$node = node_load($nid);

    $fname = $node->field_name_last['und'][0]['value'];
    $lname = $node->field_name_first['und'][0]['value'];

    $maiden_name = $node->field_name_maiden['und'][0]['value'];
    $middle_name = $node->field_name_middle['und'][0]['value'];

    $suffix = $node->field_name_suffix['und'][0]['value'];
    $gender = $node->field_gender['und'][0]['value'];
    $address_ent = entity_load('field_collection_item', array($node->field_address['und'][0]['value']));

    $address = $address_ent[$node->field_address['und'][0]['value']]->field_address_full['und'][0];
    $rows[] = array('','<h3>Thanks for taking the time to complete the identity
	validation and background verification process. A
	report is being sent to Kiva Zip with your information.
	We\'ll be in touch with you regarding next steps in
	your application process. If you\'d like, use the print
	key below to print a copy of the information you
	submitted</h3>');
    $rows[] = array('Name', $suffix.' '.$fname.' '.$middle_name .' '.$lname);

    $address1   = $address["thoroughfare"];
    $address2   = $address["premise"];
    $addressCity  = $address["locality"];
    $addressState = $address["administrative_area"];
    $addressZip   = $address["postal_code"];
    $addressZip   = $address["country"];
    $addresshtml = $address1;
    if($address2 <> ''){
	 $addresshtml .= '<br>'.$address2;
   }
    $addresshtml .= '<br>'.$addressCity;
    $addresshtml .= '<br>'.$addressState.' '.$addressZip;
    $addresshtml .= '<br>'.$addressCountry;

    $rows[] = array('Address', $addresshtml);
    $rows[] = array(drupal_render(drupal_get_form('_print_form')),drupal_render(drupal_get_form('_exit_form')));
    $header = array('','');



	return theme('table', array(
	    'header' => $header,
	    'rows' => $rows,
	    'attributes' => array('width' => '100%')
	));
}

function _print_form($form, &$form_state){

	$form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Print'),
      '#name' => 'print',
      '#attributes' => array('onclick' => 'window.print()'),
      '#submit' => array('kba_wizard_print'),
    );

    return $form;
}

function _exit_form($form, &$form_state){

	$form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Leave'),
      '#name' => 'exit',
      '#submit' => array('kba_wizard_exit'),
    );

    return $form;
}

function kba_wizard_print(){
	drupal_set_message("Printing");
	return;

}

function kba_wizard_exit(){
	module_load_include('pages.inc', 'user');
	user_logout();
	drupal_goto('/user/logout');
}

/**
 * Called when the user has failed the KBA process
 *
 * @param array The form state when user failed
 * @param int The KBA error code
 */
function kba_failed($form_state, $error_code) {

    $node = node_load($form_state['node']);


           $count_ter = field_get_items('node', $node, 'field_verify_count');
           $count = $node->field_verify_count['und'][0]['value'];

           if($count > 2){
           		    drupal_set_message("You have exceeded the limit for attempts. If you need to try again, ..");
           		    drupal_goto('verification/'.$node->nid.'/status');
           		   }
           $count = $count + 1;
           $node->field_verify_count['und'][0]['value'] = $count;
		   field_attach_update('node', $node);


	switch ($error_code) {
	    case 1:
	        $error = "The Name, DOB, or SSN do not match. Please verify your information is entered correctly. If not, please correct the information and try again. If you feel the information entered is correct, please contact Early IQ <a href='/contact'>here</a>";
	        break;
	    case 2:
	        $error = "The Name, DOB, or SSN do not match. Please verify your information is entered correctly. If not, please correct the information and try again. If you feel the information entered is correct, please contact Early IQ <a href='/contact'>here</a>.";
	        break;
	    case 3:
	        $error = "Sorry. We weren't able to verify your identity.";
	        drupal_set_message($error,'status');
	        _eiq_partners_notify_analyst($form_state['node'], 'fail');
	        module_load_include('pages.inc', 'user');
			user_logout();
		    drupal_goto('verification/'.$form_state['node'].'/status');
	        break;
	    case 4:
		    $error = "You have missed the follow up question";

		    drupal_set_message($error,'status');
	        _eiq_partners_notify_analyst($form_state['node'], 'fail');
	        module_load_include('pages.inc', 'user');
			user_logout();
		    drupal_goto('verification/'.$form_state['node'].'/status');
		break;
	}


	drupal_set_message($error,'status');
    drupal_goto('node/'.$form_state['node'].'/edit');




}



















/******************************************************************************************
                             REMOVE BELOW AFTER TESTING
 *****************************************************************************************/




/**
 * Pretty-print JSON string
 *
 * Use 'format' option to select output format - currently html and txt supported, txt is default
 * Use 'indent' option to override the indentation string set in the format - by default for the 'txt' format it's a tab
 *
 * @param string $json Original JSON string
 * @param array $options Encoding options
 * @return string
 */
function json_pretty($json, $options = array())
{
    $tokens = preg_split('|([\{\}\]\[,])|', $json, -1, PREG_SPLIT_DELIM_CAPTURE);
    $result = '';
    $indent = 0;

    $format = 'txt';

    //$ind = "\t";
    $ind = "    ";

    if (isset($options['format'])) {
        $format = $options['format'];
    }

    switch ($format) {
        case 'html':
            $lineBreak = '<br />';
            $ind = '&nbsp;&nbsp;&nbsp;&nbsp;';
            break;
        default:
        case 'txt':
            $lineBreak = "\n";
            //$ind = "\t";
            $ind = "    ";
            break;
    }

    // override the defined indent setting with the supplied option
    if (isset($options['indent'])) {
        $ind = $options['indent'];
    }

    $inLiteral = false;
    foreach ($tokens as $token) {
        if ($token == '') {
            continue;
        }

        $prefix = str_repeat($ind, $indent);
        if (!$inLiteral && ($token == '{' || $token == '[')) {
            $indent++;
            if (($result != '') && ($result[(strlen($result) - 1)] == $lineBreak)) {
                $result .= $prefix;
            }
            $result .= $token . $lineBreak;
        } elseif (!$inLiteral && ($token == '}' || $token == ']')) {
            $indent--;
            $prefix = str_repeat($ind, $indent);
            $result .= $lineBreak . $prefix . $token;
        } elseif (!$inLiteral && $token == ',') {
            $result .= $token . $lineBreak;
        } else {
            $result .= ( $inLiteral ? '' : $prefix ) . $token;

            // Count # of unescaped double-quotes in token, subtract # of
            // escaped double-quotes and if the result is odd then we are
            // inside a string literal
            if ((substr_count($token, "\"") - substr_count($token, "\\\"")) % 2 != 0) {
                $inLiteral = !$inLiteral;
            }
        }
    }
    return $result;
}

/** Prettifies an XML string into a human-readable and indented work of art
 *  @param string $xml The XML as a string
 *  @param boolean $html_output True if the output should be escaped (for use in HTML)
 */
function xmlpp($xml, $html_output=false) {
    $xml_obj = new SimpleXMLElement($xml);
    $level = 4;
    $indent = 0; // current indentation level
    $pretty = array();

    // get an array containing each XML element
    $xml = explode("\n", preg_replace('/>\s*</', ">\n<", $xml_obj->asXML()));

    // shift off opening XML tag if present
    if (count($xml) && preg_match('/^<\?\s*xml/', $xml[0])) {
      $pretty[] = array_shift($xml);
    }

    foreach ($xml as $el) {
      if (preg_match('/^<([\w])+[^>\/]*>$/U', $el)) {
          // opening tag, increase indent
          $pretty[] = str_repeat(' ', $indent) . $el;
          $indent += $level;
      } else {
        if (preg_match('/^<\/.+>$/', $el)) {
          $indent -= $level;  // closing tag, decrease indent
        }
        if ($indent < 0) {
          $indent += $level;
        }
        $pretty[] = str_repeat(' ', $indent) . $el;
      }
    }
    $xml = implode("\n", $pretty);
    return ($html_output) ? htmlentities($xml) : $xml;
}
