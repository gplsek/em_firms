<?php

require_once "classes/KBAWebService.php";

/**
 * @file
 * Extensible wizard form example.
 */

/**
 * Extensible wizard form example.
 *
 * This is an example of a multistep form using a wizard style. It will include
 * the 'Previous' and 'Next' buttons when required, and a 'Finish' button at the
 * last stage of the form submission.
 *
 * This example is an extensible skeleton that can include (even
 * programatically) more steps. The demonstration form includes three steps,
 * each step having its own validation functions.
 *
 * How to extend this example:
 * - Steps are defined in the _kba_steps() function. Include or alter
 *   the steps as you require.
 * - For each step, implement the corresponding 'form' function (see
 *   'kba_personal_info' for the first step in this example.)
 *   Each step is a regular form, and the wizard collects all the values of the
 *   included forms.
 * - Optionally, you may include custom validation functions using the regular
 *   validation hook (formname_validate). The wizard uses these validation
 *   functions for each step.
 * - The most important customization step is to change the submit handler and
 *   do whatever you want with the collected information. In this case, the
 *   example just shows the collected values in the various steps.
 * @ingroup kb
 */

/**
 * Returns the list of steps and their associated forms. This has been separated
 * to clarify and easy the understanding of this example. You should edit this
 * function to include the steps your wizard/multistep form requires.
 *
 * @return $array
 *
 * @ingroup kb
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
    );
}

/**
 * The primary formbuilder function for the wizard form. This is the form that
 * you should call with drupal_get_form() from your code, and it will include
 * the rest of the step forms defined. You are not required to change this
 * function, as this will handle all the step actions for you.
 *
 * This form has two defined submit handlers to process the different steps:
 *  - Previous: handles the way to get back one step in the wizard.
 *  - Next:     handles each step form submission,
 *
 * The third handler, the finish button handler, is the default form _submit
 * handler used to process the information.
 *
 * You are not required to change the next or previous handlers, but you must
 * change the kba_wizard_sbumit handler to perform the operations you
 * need on the collected information.
 *
 * @ingroup kb
 */
function kba_wizard($form, &$form_state) {

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

  // Show the 'previous' button if appropriate. Note that #submit is set to
  // a special submit handler, and that we use #limit_validation_errors to
  // skip all complaints about validation when using the back button. The
  // values entered will be discarded, but they will not be validated, which
  // would be annoying in a "back" button.
  if ($step > 1) {
    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#name' => 'prev',
      '#submit' => array('kba_wizard_previous_submit'),
      '#limit_validation_errors' => array(),
    );
  }

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
 */
function kba_wizard_previous_submit($form, &$form_state) {
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
 */
function kba_wizard_next_submit($form, &$form_state) {
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
 *
 */
function kba_personal_info($form, &$form_state) {
    global $user;

	$form['data_person_nid'] = array(
		'#type' => 'hidden',
		//'#default_value' => $data_nid,

	);
	$form['first_name'] = array(
		'#title' => t('First Name'),
		'#type' => 'textfield',
    '#default_value' => !empty($form_state['values']['first_name']) ? $form_state['values']['first_name'] : ''

	);
	$form['middle_name'] = array(
		'#title' => t('Middle Name'),
		'#type' => 'textfield',
		'#default_value' => !empty($form_state['values']['middle_name']) ? $form_state['values']['middle_name'] : ''
	);
	$form['last_name'] = array(
		'#title' => t('Last Name'),
		'#type' => 'textfield',
		'#default_value' => !empty($form_state['values']['last_name']) ? $form_state['values']['last_name'] : ''

	);
	/*
	$form['phone_number'] = array(
		'#title' => t('Phone Number'),
		'#type' => 'textfield',
		'#default_value' => !empty($form_state['values']['phone_number']) ? $form_state['values']['phone_number'] : ''
	);
	*/
	
	$form['birthdate'] = array(
	  '#title' => t('Birthdate'),
	  '#type' => 'date',
	  '#description' => t('Select your birthdate'),
	  '#default_value' => array(
	  	    'month' => format_date(time(), 'custom', 'n'),
	  	    'day' => format_date(time(), 'custom', 'j'),
	  	    'year' => format_date(time(), 'custom', 'Y'),
        )
	);
	$form['gender'] = array(
	  '#title' => t('Gender'),
	  '#type' => 'select',
	  '#description' => t('Select your gender'),
	  '#options' => array('Male' => 'Male', 'Female' => 'Female'),
	  '#default_value' => !empty($form_state['values']['gender']) ? $form_state['values']['gender'] : ''
	);

	$form['ssn'] = array(
		'#title' => t('Social Security Number'),
		'#type' => 'textfield',
		'#default_value' => !empty($form_state['values']['ssn']) ? $form_state['values']['ssn'] : ''
	);

	$form['address'] = array(
    '#type' => 'addressfield',
    '#title' => t('Address'),
    '#required' => TRUE,
    '#default_value' => array('country' => 'US'), // Selects USA by default
    '#description' => "Please enter your address."
  );
		  
	return $form;
}

/**
 * 
 */
function kba_questions($form, &$form_state) {
  $form = array();
  
  if(!empty($form_state["step_information"]) && !empty($form_state["step_information"][1])) {
    
    $personalInformation = $form_state["step_information"][1];
    
    $questions = _ws_verification($personalInformation["stored_values"]);
    print_r($questions);
    
  }
  
  return $form;
}

/**
 * Custom validation form for the 'location info' page of the wizard.
 *
 * This is the validation function for the second step of the wizard.
 * The city cannot be empty or be "San Francisco".
 *
 * @ingroup kb
 */
function kba_questions_validate($form, &$form_state) {
  if ($form_state['values']['city'] == 'San Francisco') {
    form_set_error('city', t('You were warned not to enter "San Francisco"'));
  }
}

/**
 * Returns form elements for the 'other info' page of the wizard. This is the
 * thid and last step of the example wizard.
 *
 * @ingroup kb
 */
function kba_follow_up_question($form, &$form_state) {
  $form = array();
  $form['aunts_name'] = array(
    '#type' => 'textfield',
    '#title' => t("Your first cousin's aunt's Social Security number"),
    '#default_value' => !empty($form_state['values']['aunts_name']) ? $form_state['values']['aunts_name'] : '',
  );
  return $form;
}

// And now comes the magic of the wizard, the function that should handle all the
// inputs from the user on each different step.
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
  drupal_set_message(t('This information was collected by this wizard:'));
  foreach ($form_state['step_information'] as $index => $value) {
    // Remove FAPI fields included in the values (form_token, form_id and form_build_id
    // This is not required, you may access the values using $value['stored_values']
    // but I'm removing them to make a more clear representation of the collected
    // information as the complete array will be passed through drupal_set_message().
    unset($value['stored_values']['form_id']);
    unset($value['stored_values']['form_build_id']);
    unset($value['stored_values']['form_token']);

    // Now show all the values.
    drupal_set_message(
        t('Step @num collected the following values: <pre>@result</pre>', 
        array('@num' => $index, '@result' => print_r($value['stored_values'], TRUE)))
    );
  }
}


function _ws_verification($data) {
  
  $options = array("login" => "EmergingFirmsINTEG", "password" => '$u85ApDR!c2', 'trace' => 1);
  $webService = new KBAWebService($options, dirname(__FILE__)."/rsa_kba.wsdl");
  
  $personID = $data["data_person_nid"];
  $firstName = $data["first_name"];
  $lastName  = $data["last_name"];
  $email     = $data["email"];
  $ssn       = $data["ssn"];
  $birthYear = $data["birthdate"]["year"];
  $birthMonth = $data["birthdate"]["month"];
  $birthDay = $data["birthdate"]["day"];
  
  $address1 = $data["address"]["address"]["thoroughfare"];
  $address2 = $data["address"]["address"]["premise"];
  $addressCity = $data["address"]["address"]["locality"];
  $addressState = $data["address"]["address"]["administrative_area"];
  $addressZip = $data["address"]["address"]["postal_code"];
  
  //$phoneNumber = $data["address"]["address"]["phone_number"];
  
  
  $requestData = array(
      "settings" => array(
          "account-name" => "Customers:EmergingFirms:CompanyApp",
          "mode" => "simulated", // simulated testing
          "simulator-mode"=>"questions",
          "ruleset" => "customers.emergingfirms.compapp.4quest",
          "task" => "iauth"
      ),
      "person" => array(
          "name-first" => $firstName,
          "name-last"  => $lastName,
          "email" => $email, // NOT REQUIRED
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
          /*
          "phone-number" => array(   // NOT REQUIRED
              "phone-number" => $phoneNumber, 
              "phone-number-context" => "home"
          )
          */
      ),
      "transaction" => array(
          "account-verification" => array(
              "account-maintenance" => array(
                  "account" => array(
                      "customer-id" => "TESTING_0001" //$personID
                  )
              ),
              "venue" => array(
                  "online" => array(
                      "credential" => array(
  				        "credential-method" => "ssn"
                      )
                  )
              ),
              "activity-date" => gmdate("c")
          )
      )
  );
  
  $results = $webService->identityVerification($requestData);
  
  return $results;
}