<?php

/**
 * Provide payment transaction revision Views integration.
 */

/**
 * Implements hook_views_data_alter().
 */
function commerce_payment_transaction_revision_views_data_alter(&$data) {
  $data['commerce_payment_transaction']['table']['default_relationship'] = array(
    'commerce_payment_transaction_revision' => array(
      'table' => 'commerce_payment_transaction_revision',
      'field' => 'revision_id',
    ),
  );
}

/**
 * Implements hook_views_data()
 */
function commerce_payment_transaction_revision_views_data() {
  $data = array();

  $data['commerce_payment_transaction_revision']['table']['entity type'] = 'commerce_payment_transaction';
  $data['commerce_payment_transaction_revision']['table']['group']  = t('Commerce Payment Transaction revision');

  // Advertise this table as a possible base table.
  $data['commerce_payment_transaction_revision']['table']['base'] = array(
    'field' => 'revision_id',
    'title' => t('Commerce Payment Transaction revision'),
    'help' => t('Commerce Payment Transaction revision is a history of changes to a payment transaction.'),
    'defaults' => array(
      'field' => 'revision_id',
    ),
  );

  $data['commerce_payment_transaction_revision']['table']['join'] = array(
    'commerce_payment_transaction' => array(
      'left_field' => 'revision_id',
      'field' => 'revision_id',
    ),
  );

  $data['commerce_payment_transaction_revision']['table']['default_relationship'] = array(
    'commerce_payment_transaction' => array(
      'table' => 'commerce_payment_transaction',
      'field' => 'revision_id',
    ),
  );

  // Expose the revision transaction ID.
  $data['commerce_payment_transaction_revision']['transaction_id'] = array(
    'title' => t('Transaction ID', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The unique internal identifier of the payment transaction.'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the revision ID.
  $data['commerce_payment_transaction_revision']['revision_id'] = array(
    'title' => t('Revision ID', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The ID of the payment transaction revision.'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_payment_transaction',
      'base field' => 'revision_id',
      'title' => t('Payment transaction'),
      'label' => t('Latest payment transaction revision'),
    ),
  );

  // Expose the revision user ID.
  $data['commerce_payment_transaction_revision']['revision_uid'] = array(
    'title' => t('User', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('Relate a payment transaction revision to the user who created the revision.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'field' => 'revision_uid',
      'field_name' => 'revision_uid',
      'label' => t('Revision user', array(), array('context' => 'a drupal commerce order')),
    ),
  );


  // Expose the revision order ID.
  $data['commerce_payment_transaction_revision']['order_id'] = array(
    'title' => t('Order ID', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The unique internal identifier of the associated order at this revision.'),
    'field' => array(
      'handler' => 'commerce_order_handler_field_order',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'commerce_order_handler_argument_order_order_id',
      'name field' => 'order_number',
      'numeric' => TRUE,
      'validate type' => 'order_id',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'field' => 'order_id',
      'label' => t('Revision order', array(), array('context' => 'a drupal commerce order')),
    ),
  );

  // Expose the payment transaction revision payment method.
  $data['commerce_payment_transaction_revision']['payment_method'] = array(
    'title' => t('Payment method', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The payment method of the transaction at this revision.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_payment_method',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_payment_handler_filter_payment_method',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the payment transaction revision remote ID.
  $data['commerce_payment_transaction_revision']['remote_id'] = array(
    'title' => t('Remote ID', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The remote identifier of this transaction at the payment provider at this revision.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the payment transaction revision amount.
  $data['commerce_payment_transaction_revision']['amount'] = array(
    'title' => t('Amount', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The amount of the transaction at this revision.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_amount',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the payment transaction revision currency.
  $data['commerce_payment_transaction_revision']['currency_code'] = array(
    'title' => t('Currency', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The currency of the transaction at this revision.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_currency_code',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_payment_handler_filter_currency_code',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the payment transaction revision message.
  $data['commerce_payment_transaction_revision']['message'] = array(
    'title' => t('Message', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The message associated with the transaction at this revision.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_message',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the payment transaction revision status.
  $data['commerce_payment_transaction_revision']['status'] = array(
    'title' => t('Status', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The status of this transaction at this revision.'),
    'field' => array(
      'handler' => 'commerce_payment_handler_field_status',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_payment_handler_filter_payment_transaction_status',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the payment transaction revision remote status.
  $data['commerce_payment_transaction_revision']['remote_status'] = array(
    'title' => t('Remote status', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The status of this transaction at the payment provider at this revision.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the payment transaction revision log message.
  $data['commerce_payment_transaction_revision']['log'] = array(
    'title' => t('Log message', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The log message entered when this payment transaction revision was created.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // Expose the payment transaction revision timestamp.
  $data['commerce_payment_transaction_revision']['revision_timestamp'] = array(
    'title' => t('Revision date', array(), array('context' => 'a drupal commerce payment transaction')),
    'help' => t('The date when this payment transaction revision was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}
